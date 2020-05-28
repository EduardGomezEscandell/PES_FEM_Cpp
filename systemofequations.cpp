#include "systemofequations.h"


SystemOfEquations::SystemOfEquations()
{

}

void SystemOfEquations::assemble(Domain domain, QuadData qdata){
//    K_coo.reserve(5 * domain.n_nodes); // Quick approximation of expected no of entries

    size = domain.n_nodes + dirichlet_nodes.size();
    F = Eigen::VectorXd::Zero(size);

    for(ElementT1 *E = domain.elementsT1; E->id >=0; E++){

        E->calc_jacobian();

        Eigen::Matrix3d k_local;
        k_local <<0, 0, 0,
                  0, 0, 0,
                  0, 0, 0;

        for(QuadPoint *q=qdata.points; q->w >= 0; q++){
            Eigen::MatrixXd gradN;
            gradN = E->jacobian.inverse() * q->gradN;

            k_local += q->w * (gradN.transpose() * gradN);
        }

        k_local *= E->get_area() / qdata.total_weight;

        for(int i=0; i<3; i++){
            for(int j=0; j<3; j++){
                K_coo.emplace_back(E->nodes[i].id, E->nodes[j].id, k_local(i,j));
            }
        }
    }

    // Dirichlet Boundary condition via the penalty method
    for(size_t i=0; i<dirichlet_nodes.size(); i++)
    {
        int boc = i + domain.n_nodes;     // Its ID as a boundary condition
        int dof = dirichlet_nodes[i]->id; // Its ID as a dof

        K_coo.emplace_back(boc, dof, 1.0);
        K_coo.emplace_back(dof, boc, 1.0);
        K_coo.emplace_back(boc, boc, inv_penalty);

        F(boc) += dirichlet_nodes[i]->bc_value;
    }

    // Neumann Boundary conditions via addition to load vector
    for(size_t i=0; i<neumann_nodes.size(); i++)
    {
        int dof = neumann_nodes[i]->id; // Its ID as a dof
        F(dof) += neumann_nodes[i]->bc_value;
    }

    // Switching sparse matrix type to CSR
    K = SpMat(size, size);
    K.setFromTriplets(K_coo.begin(), K_coo.end());
    K.makeCompressed();
}

void SystemOfEquations::load_bc(Domain dom, std::string filename)
{
    std::ifstream inFile;
    inFile.open(filename);

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
        if(node_id >= (int) dom.n_nodes){
            throw "Boundary file includes nodes not present in the coordinates file";
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
            throw "Unrecognized BC type in boundaries file";
        }

        // Parsing value
        double bc_value = stod(data[2]);

        // Ignoring NONE and Neumann=0
        if((bc_type==BC_NONE) || (bc_type == BC_NEUMANN && bc_value == 0)){
            continue;
        }

        // Storing info
        Node * this_node = &(dom.nodes[node_id]);
        this_node->bc_value = bc_value;
        this_node->bc_type = bc_type;
        switch(bc_type){
        case BC_DIRICHLET:
            dirichlet_nodes.push_back(this_node);
            break;
        case BC_NEUMANN:
            neumann_nodes.push_back(this_node);
            break;
        }

    }
}

double SystemOfEquations::solve(){
    Eigen::SimplicialCholesky<SpMat> chol(K);
    U = chol.solve(F);
    Eigen::VectorXd R= F - K*U;
    return R.norm();
}

void SystemOfEquations::plot_sparsity(std::string filename){
    /*
     * Plots the sparsity pattern of the system matrix as a bitmap.
     * Using PBM format. Wikipedia's page is decent: https://en.wikipedia.org/wiki/Netpbm#File_formats
     */
    std::ofstream outpFile;
    outpFile.open(filename);

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

void SystemOfEquations::export_result(std::string filename){

    std::ofstream outFile;
    outFile.open(filename);

    int n_nodes = size - dirichlet_nodes.size(); // Redundant but this way we don't need to call domain

    for(int i = 0; i<n_nodes; i++){
        outFile << U(i)<<std::endl;
    }
    outFile.close();
}
