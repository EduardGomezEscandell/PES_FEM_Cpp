#include "systemofequations.h"


SystemOfEquations::SystemOfEquations()
{

}

void SystemOfEquations::assemble(Domain * domain){
//    K_coo.reserve(5 * domain.n_nodes); // Quick approximation of expected no of entries

    size = domain->n_nodes() + dirichlet_nodes.size();
    F = Eigen::VectorXd::Zero(size);

    for(T1_iterator E = domain->T1ptr(); E->id >=0; E++){
        ASSEMBLE_LOCAL(K_coo, E);
    }
    for(T2_iterator E = domain->T2ptr(); E->id >=0; E++){
        ASSEMBLE_LOCAL(K_coo, E);
    }
    for(Q1_iterator E = domain->Q1ptr(); E->id >=0; E++){
        ASSEMBLE_LOCAL(K_coo, E);
    }
    for(Q2_iterator E = domain->Q2ptr(); E->id >=0; E++){
        ASSEMBLE_LOCAL(K_coo, E);
    }

    // Dirichlet boundary conditions via the penalty method
    for(size_t i=0; i<dirichlet_nodes.size(); i++)
    {
        int boc = i + domain->n_nodes();     // Its ID as a boundary condition (starts at n_nodes)
        int dof = dirichlet_nodes[i]->id;   // Its ID as a dof

        K_coo.emplace_back(boc, dof, 1.0);
        K_coo.emplace_back(dof, boc, 1.0);
        K_coo.emplace_back(boc, boc, inv_penalty);

        F(boc) += dirichlet_nodes[i]->bc_value;
    }

    // Neumann boundary condition by addition to load vector
    for(Eg_iterator Eg = neumann_edges.begin(); Eg!= neumann_edges.end(); Eg++){
        Eigen::VectorXd q_local(Eg->n_nodes);
        for(int i=0; i<Eg->n_nodes; i++){
            q_local(i) = Eg->nodes[i]->bc_value;
        }
        Eigen::MatrixXd M_local(Eg->n_nodes, Eg->n_nodes);
        for(qiterator q=Eg->qdata->points.begin(); q->w >= 0; q++){
            M_local += q->w * q->N.transpose() * q->N;
        }
        M_local *= Eg->length / Eg->qdata->total_weight;
        Eigen::VectorXd F_local = M_local * q_local;

        for(int i=0; i<Eg->n_nodes; i++){
            int id = Eg->nodes[i]->id;
            F(id) += F_local(i);
        }
    }

    // Switching sparse matrix type to CSR
    K = SpMat(size, size);
    K.setFromTriplets(K_coo.begin(), K_coo.end());
    K.makeCompressed();
}

void SystemOfEquations::load_bc(Domain * domain, Settings settings)
{
    std::ifstream inFile;
    inFile.open(settings.boco_filename);

    std::string line;

    while(!inFile.eof())
    {
        getline(inFile, line);

        if(line[0] == '\0'){
            // Skip empty lines
            continue;
        }

        std::vector<std::string> data = split_string(line, '\t');

        // Removing invalid nodes (avoiding SEGFAULT)
        int node_id = stoi(data[1]) - 1; // File uses 1-indexed counting and C++ uses 0-indexed
        if(node_id >= (int) domain->n_nodes()){
            std::cerr<<"Boundary file includes nodes not present in the coordinates file"<<std::endl;
            throw -1;
        }

        // Parsing boundary type
        char bc_char = data[0][0];
        int bc_type;
        switch (bc_char) {
        case 'D':
            bc_type = BC_DIRICHLET;
            break;
        case 'N':
            bc_type = BC_NEUMANN;
            break;
        case '0':
            bc_type = BC_NONE;
            break;
        default:
            std::cerr<<"Unrecognized BC type in boundaries file"<<std::endl;
            throw -1;
        }

        // Parsing value
        double bc_value = stod(data[2]);

        // Ignoring NONE and Neumann=0
        if((bc_type==BC_NONE) || (bc_type == BC_NEUMANN && bc_value == 0)){
            continue;
        }

        // Storing info
        Node * this_node = &(domain->nodes[node_id]);
        this_node->bc_value = bc_value;
        this_node->bc_type = bc_type;
        if(bc_type == BC_DIRICHLET){
            dirichlet_nodes.push_back(this_node);
        }

    }

    for(T1_iterator E = domain->T1ptr(); E->id >=0; E++){
        CREATE_NEUMANN_EDGES(E, neumann_edges, domain, qadta);
    }
    for(T2_iterator E = domain->T2ptr(); E->id >=0; E++){
        CREATE_NEUMANN_EDGES(E, neumann_edges, domain, qadta);
    }
    for(Q1_iterator E = domain->Q1ptr(); E->id >=0; E++){
        CREATE_NEUMANN_EDGES(E, neumann_edges, domain, qadta);
    }
    for(Q2_iterator E = domain->Q2ptr(); E->id >=0; E++){
        CREATE_NEUMANN_EDGES(E, neumann_edges, domain, qadta);
    }

}

double SystemOfEquations::solve(){
    // Solves the system
    Eigen::SimplicialCholesky<SpMat> chol(K);
    U = chol.solve(F);
    Eigen::VectorXd R= F - K*U;
    return R.norm();
}

double SystemOfEquations::solve(Domain * dom){
    // Solves and stores the values at the nodes
    double error_norm = solve();

    for(N_iterator n = dom->Nptr(); n->id >=0; n++){
        n->u = U(n->id);
    }

    return error_norm;
}

void SystemOfEquations::plot_sparsity(Settings settings){
    /*
     * Plots the sparsity pattern of the system matrix as a bitmap.
     * Using PBM format. Wikipedia's page gives a good overview:
     * https://en.wikipedia.org/wiki/Netpbm#File_formats
     */
    std::ofstream outpFile;
    try{
        outpFile.open(settings.directory + "sparsity_patern.pbm");
    } catch (...) {
        outpFile.open("../PES_FEM_Cpp/results/sparsity_pattern.pbm");
    }

    outpFile<<"P1"<<std::endl;             // B&W format
    outpFile<<"# Computer-generated file. Sparsity pattern of a 2D Laplacian matrix."<<std::endl;
    outpFile<<size<<" "<<size<<std::endl;  // Image size

    int * outer_ptr = K.outerIndexPtr();
    int * inner_ptr = K.innerIndexPtr();

    int curr_col;
    // Traversing rows
    for(size_t row=0; row<size; row++){
        curr_col = 0;

        // Traversing columns
        for(int i = outer_ptr[row]; i<outer_ptr[row+1]; i++){
            int col = inner_ptr[i];

            // Filing with white until next non-zero value
            for(; curr_col < col; curr_col++){
                outpFile<<"0 ";
            }
            // Putting a black pixel at the non-zero value
            outpFile<<"1 ";
            curr_col++;
        }
        // Filling rest of row with white pixels
        for(; curr_col < (int) size; curr_col++){
            outpFile<<"0 ";
        }
        outpFile<<std::endl;
    }

    outpFile.close();
}
