#include "domain.h"

Domain::Domain(std::string node_file, std::string mesh_file)
{
    // Importing nodes

    size_t max_node = 200;          // Current memory allocated
    size_t size_increment = 200;    // Increase of memory at realloc
    n_nodes = 0;

    // Allocating nodes array
    nodes = (Node *) malloc(max_node * sizeof(*nodes));

    // Opening coordinates file
    std::ifstream inFile;
    inFile.open(node_file);

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
    inFile.open(mesh_file);

    size_t max_elem = 0;            // Current memory allocated
    size_increment = 200;           // Increase of memory at realloc
    n_elems = 0;

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
        if(n_elems == 0){
            nodes_per_elem = data.size();
            switch(nodes_per_elem){
            case 3:
                max_elem += n_elems;
                elementsT1 = (ElementT1*) malloc(max_elem * sizeof(ElementT1));
                break;
            default:
                throw "Element type not implemented";
            }
        }
        // Check that all subsequent elements are of the same type
        else if(data.size() != nodes_per_elem) {
            throw "Inconsistent element type";
        }

        // If it runs out of memory, increase it
        if(n_elems == max_elem){
            max_elem += size_increment;
            elementsT1 = (ElementT1 *) realloc(elementsT1, max_elem * sizeof(*elementsT1));
            if(elementsT1 == NULL){
                free(elementsT1);
                throw "Failed to reallocate element list";
            }
        }

        // Reading the connectivity
        int *node_ids = (int *)malloc(data.size() * sizeof (int));
        for(size_t i=0; i<data.size(); i++){
            node_ids[i] = stoi(data[i]) - 1; // Changing to 0-indexing
        }

        // Creating Element object
        switch(nodes_per_elem){
        case 3:
            elementsT1[n_elems] = ElementT1(n_elems, nodes, node_ids);
            n_elems++;
            break;
        }
    }

     //Adding sentinel
    switch(nodes_per_elem){
    case 3:
        if(n_elems == max_elem){
            max_elem += 1;
            elementsT1 = (ElementT1 *) realloc(elementsT1, max_elem * sizeof(*elementsT1));
        }
        elementsT1[n_elems] = ElementT1();
        n_elems++;
        break;
    }

    inFile.close();
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
            sprintf(buffer," %5d", E->nodes[n].id);
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
            sprintf(buffer," %5d", E->nodes[n].id);
            fileOut<<buffer;
        }
        fileOut<<std::endl;
    }
    fileOut.close();
}

