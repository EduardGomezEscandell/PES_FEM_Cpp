//#include "domain.h"

//Domain::Domain(std::string node_file, std::string mesh_file)
//{
//    // Importing nodes

//    std::ifstream inFile;
//    inFile.open(node_file);

//    std::string line;

//    while(!inFile.eof()){
//        getline(inFile, line);

//        if(line[0]=='\0'){
//            // Empty line
//            continue;
//        }

//        std::vector<std::string> data = split_string(line, ' ');

//        int id = Domain::nodes.size();
//        double x = stod(data[1]);
//        double y = stod(data[2]);

//        // Create and append a new node:
//        Domain::nodes.emplace_back(id, x, y);
//    }

//    // Importing elements

//    inFile.close();
//    inFile.open(mesh_file);

//    size_t max_elem = 0;            // Current memory allocated
//    size_t size_increment = 200;    // Increase of memory at realloc

//    size_t nodes_per_elem;          // Nodes per element

//    while(!inFile.eof()){

//        getline(inFile, line);

//        if(line[0]=='\0'){
//            // Empty line
//            continue;
//        }

//        std::vector<std::string> data = split_string(line, ' ');

//        // Parse the element type at the first iteration
//        if(n_elems == 0){
//            nodes_per_elem = data.size();
//            switch(nodes_per_elem){
//            case 3:
//                elements = (ElementT1*) malloc(size_increment * sizeof(ElementT1));
//                break;
//            default:
//                throw "Element type not implemented";
//            }
//        }
//        // Check that all subsequent elements are of the same type
//        else if(data.size() != nodes_per_elem) {
//            throw "Inconsistent element type";
//        }

//        // If it runs out of memory, increase it
//        if(n_elems == max_elem){
//            max_elem += size_increment;
//            elements = realloc(elements, max_elem * sizeof(elements[0]);
//            if(elements == NULL){
//                free(elements);
//                throw "Failed to reallocate element list";
//            }
//        }

//        int node_ids[data.size()];
//        for(size_t i=0; i<data.size(); i++){
//            node_ids[i] = stoi(data[i]);
//        }

//        switch(nodes_per_elem){
//        case 3:
//            elements = (ElementT1*) malloc(size_increment * sizeof(ElementT1));
//            break;
//        }

//    }
//    inFile.close();
//}
