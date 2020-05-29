#include "domain.h"

Domain::Domain(Settings settings)
{
    /*
     *
     *  Importing nodes
     *
     */

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
        int id = nodes.size();
        double x = stod(data[1]);
        double y = stod(data[2]);

        // Adding new node
        nodes.emplace_back(id, x, y);
    }

     // Adding setinel
    nodes.emplace_back();

    /*
     *
     * Importing elements
     *
     */

    inFile.close();
    inFile.open(settings.mesh_filename);

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
        int id = elementsT1.size();
        // Reading the connectivity
        std::vector<int> node_ids;
        for(size_t i=0; i<data.size(); i++){
            node_ids.push_back(stoi(data[i]) - 1); // Changing to 0-indexing
        }

        switch (nodes_per_elem) {
        case 3:
            elementsT1.emplace_back(id, &nodes, node_ids);
            break;
        case 9:
            //
            break;
        default:
            std::cerr<<"Unrecognized element type"<<std::endl;
            throw -1;
        }
    }

     //Adding sentinels
    elementsT1.emplace_back();
    elementsQ2.emplace_back();

    inFile.close();
}

void Domain::printnodes(){
    // Prints the coordinates to the console. NOT TESTED.
    for(N_iterator n = Nptr(); n->id >=0; n++)
    {
        printf("%8.5f, %8.5f\n",n->coordinates[0], n->coordinates[1]);
    }
}

void Domain::printnodes(std::string filename)
{
    // Prints the coordinates to a file. NOT TESTED.
    std::ofstream fileOut;
    fileOut.open(filename);
    for(N_iterator n = Nptr(); n->id >=0; n++){
        char buffer[200];
        sprintf(buffer, "%8.5f, %8.5f\n",n->coordinates[0], n->coordinates[1]);
        fileOut<<buffer;
    }
    fileOut.close();
}

void Domain::calc_gradients(){
    QuadData qdataT1(3);
    qdataT1.initialize_shape_functions(3);

    for(T1_iterator E = T1ptr(); E->id >=0; E++){
        calc_gradient(E, qdataT1);
    }

//    for(Q2_iterator E = Q2ptr(); E->id >=0; E++){
//        calc_gradient(E, qdataT1);
//    }


    gradients_calculated = true;
}


void Domain::export_result(std::string filename){

    std::ofstream outFile;
    outFile.open(filename);

    if(gradients_calculated){
        // Printing solution and gradients
        for(N_iterator n = Nptr(); n->id >=0; n++){
            char buffer [100];
            sprintf(buffer, "%10.6f %10.6f %10.6f\n", n->u, n->grad_u(0), n->grad_u(1));
            outFile<< buffer;
        }
    } else {
        // Printing only the solution
        for(N_iterator n = Nptr(); n->id >=0; n++){
                char buffer [100];
                sprintf(buffer, "%10.6f\n", n->u);
                outFile<< buffer;
        }
    }

    outFile.close();
}

T1_iterator Domain::T1ptr(){
    return elementsT1.begin();
}

Q2_iterator Domain::Q2ptr(){
    return elementsQ2.begin();
}

N_iterator Domain::Nptr(){
    return nodes.begin();
}

size_t Domain::n_nodes(){
    // Sentinel does not count!
    return nodes.size() - 1;
}

size_t Domain::n_elems(){
   //Sentinels do not count!
   return -2 + elementsT1.size() + elementsQ2.size();
//   return -4 + elementsT1.size() + elementsQ2.size() +elementsT2.size() + elementsQ1.size();
}
