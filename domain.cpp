#include "domain.h"

Domain::Domain(Settings settings)
{
    // Importing nodes

    size_t max_node = 200;          // Current memory allocated
    size_t size_increment = 200;    // Increase of memory at realloc
    n_nodes = 0;

    // Allocating nodes array
    nodes = (Node *) malloc(max_node * sizeof(*nodes));

    // Opening coordinates file
    std::ifstream inFile;
    inFile.open(settings.node_filename);

    while(!inFile.eof()){
        std::string line;
        getline(inFile, line);

        // Skipping empty lines
        if(line[0]=='\0'){
            continue;
        }

        // Parsing data
        std::vector<std::string> data = split_string(line, ' ');
        int id = n_nodes;
        double x = stod(data[1]);
        double y = stod(data[2]);

        // Check if there is memory left. Otherwise increase it
        if(n_nodes == max_node){
            max_node += size_increment;
            nodes = (Node *) realloc(nodes, max_node * sizeof(*nodes));
        }

        // Adding new node
        nodes[n_nodes] = Node(id, x, y);
        n_nodes += 1;
    }

     // Adding setinel
    if(n_nodes == max_node){
        max_node += 1;
        nodes = (Node *) realloc(nodes, max_node * sizeof(*nodes));
    }
    nodes[n_nodes] = Node();

    // Importing elements

    inFile.close();
    inFile.open(settings.mesh_filename);

    size_t max_elem_T1 = 0;            // Current memory allocated
//    size_t max_elem_T2 = 0;
//    size_t max_elem_Q1 = 0;
    size_t max_elem_Q2 = 0;

    size_increment = 200;           // Increase of memory at realloc

    n_elemsT1 = 0;
    n_elemsT2 = 0;
    n_elemsQ1 = 0;
    n_elemsQ2 = 0;

    size_t nodes_per_elem;          // Nodes per element

    std::vector<std::string> data;
    std::string line;

    while(!inFile.eof()){

        std::getline(inFile, line);

        if(line[0]=='\0'){
            // Empty line
            continue;
        }

        data = split_string(line, ' ');

        // Parse the element type at the first iteration
        nodes_per_elem = data.size();

        // Reading the connectivity
        int *node_ids = (int *)malloc(data.size() * sizeof (int));
        for(size_t i=0; i<data.size(); i++){
            node_ids[i] = stoi(data[i]) - 1; // Changing to 0-indexing
        }

        switch (nodes_per_elem) {
        case 3:
            new_T1_element(node_ids, &max_elem_T1, size_increment);
            break;
        case 9:
            new_Q2_element(node_ids, &max_elem_Q2, size_increment);
            break;
        default:
            throw "Unrecognized element type";
        }


    }

     //Adding sentinels

    if(n_elemsT1 == max_elem_T1){
        max_elem_T1 += 1;
        elementsT1 = (ElementT1 *) realloc(elementsT1, max_elem_T1 * sizeof(*elementsT1));
    }
    elementsT1[n_elemsT1] = ElementT1();


    inFile.close();
}

void Domain::new_T1_element(int * node_ids, size_t * max_elem, size_t size_increment){
    if(n_elemsT1 == 0){
        *max_elem += n_elemsT1;
        elementsT1 = (ElementT1*) malloc(*max_elem * sizeof(ElementT1));
    }

    // If it runs out of memory, increase it
    if(n_elemsT1 == *max_elem){
        *max_elem += size_increment;
        elementsT1 = (ElementT1 *) realloc(elementsT1, *max_elem * sizeof(*elementsT1));
        if(elementsT1 == NULL){
            free(elementsT1);
            throw "Failed to reallocate element list";
        }
    }

    // Creating Element object
    elementsT1[n_elemsT1] = ElementT1(n_elemsT1, nodes, node_ids);
    n_elemsT1++;
}


void Domain::new_Q2_element(int * node_ids, size_t * max_elem, size_t size_increment){
    if(n_elemsQ2 == 0){
        max_elem += n_elemsQ2;
        elementsQ2 = (ElementQ2*) malloc(*max_elem * sizeof(ElementQ2));
    }

    // If it runs out of memory, increase it
    if(n_elemsQ2 == *max_elem){
        *max_elem += size_increment;
        elementsQ2 = (ElementQ2 *) realloc(elementsQ2, *max_elem * sizeof(*elementsQ2));
        if(elementsQ2 == NULL){
            free(elementsQ2);
            throw "Failed to reallocate element list";
        }
    }

    // Creating Element object
    elementsQ2[n_elemsQ2] = ElementQ2(n_elemsQ2, nodes, node_ids);
    n_elemsQ2++;
}



void Domain::printnodes(){
    // Prints the coordinates to the console. NOT TESTED.
    for(Node *n = nodes; n->id >=0; n++)
    {
        printf("%8.5f, %8.5f\n",n->coordinates[0], n->coordinates[1]);
    }
}

void Domain::printnodes(std::string filename)
{
    // Prints the coordinates to a file. NOT TESTED.
    std::ofstream fileOut;
    fileOut.open(filename);
    for(Node *n = nodes; n->id >=0; n++){
        char buffer[200];
        sprintf(buffer, "%8.5f, %8.5f\n",n->coordinates[0], n->coordinates[1]);
        fileOut<<buffer;
    }
    fileOut.close();
}


void Domain::printelems()
{
    // Prints the connectivities to the console. NOT TESTED.
    char buffer[100];
    for(ElementT1 *E = elementsT1; E->id >= 0; E++){
        sprintf(buffer, "%5d:",E->id);
        std::cout<<buffer;
        for(int n=0; n < E->n_nodes; n++){
            sprintf(buffer," %5d", E->nodes[n]->id);
            std::cout<<buffer;
        }
        std::cout<<std::endl;
    }
}

void Domain::printelems(std::string filename)
{
    // Prints the connectivities in a file. NOT TESTED.
    std::ofstream fileOut;
    fileOut.open(filename);
    char buffer[100];

    for(ElementT1 *E = elementsT1; E->id >= 0; E++){
        sprintf(buffer, "%5d:",E->id);
        fileOut<<buffer;
        for(int n=0; n < E->n_nodes; n++){
            sprintf(buffer," %5d", E->nodes[n]->id);
            fileOut<<buffer;
        }
        fileOut<<std::endl;
    }
    fileOut.close();
}

size_t Domain::n_elems(){
    return n_elemsT1 + n_elemsT2 + n_elemsQ1 + n_elemsQ2;
}

void Domain::calc_gradients(QuadData qdata_corners_T1){
    qdata_corners_T1.initialize_shape_functions(3);

    for(ElementT1 * E = elementsT1; E->id >=0; E++){
        Eigen::Vector3d U_local;
        for(int i=0; i<E->n_nodes; i++){
            U_local(i) = E->nodes[i]->u;
        }

        Eigen::MatrixXd gradU = Eigen::MatrixXd::Zero(2,E->n_nodes);
        Node ** n = E->nodes;
        for(QuadPoint * q=qdata_corners_T1.points; q->w >= 0; q++){
            Eigen::MatrixXd gradN = E->invJacobian * q->gradN;
            (**n).grad_u = gradN * U_local;
            n++;
        }
    }
    gradients_calculated = true;
}


void Domain::export_result(std::string filename){

    std::ofstream outFile;
    outFile.open(filename);

    if(gradients_calculated){
        // Printing solution and gradients
        for(Node * n = nodes; n->id >=0; n++){
            char buffer [100];
            sprintf(buffer, "%10.6f %10.6f %10.6f\n", n->u, n->grad_u(0), n->grad_u(1));
            outFile<< buffer;
        }
    } else {
        // Printing only the solution
        for(Node * n = nodes; n->id >=0; n++){
                char buffer [100];
                sprintf(buffer, "%10.6f\n", n->u);
                outFile<< buffer;
        }
    }

    outFile.close();
}
