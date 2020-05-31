#include "domain.h"

Domain::Domain(Settings settings, QuadData * quadratures)
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

        // Reading the connectivity
        std::vector<int> node_ids;
        for(size_t i=0; i<data.size(); i++){
            node_ids.push_back(stoi(data[i]) - 1); // Changing to 0-indexing
        }
        int id = n_elems() + 4; // Sentinels not yet placed
        switch (nodes_per_elem) {
        case 3:
            elementsT1.emplace_back(id, &nodes, node_ids);
            elementsT1.back().qdata = &quadratures[0];
            elementsT1.back().qdata_line = &quadratures[4];
            break;
        case 4:
            elementsQ1.emplace_back(id, &nodes, node_ids);
            elementsQ1.back().qdata = &quadratures[2];
            elementsQ1.back().qdata_line = &quadratures[4];
            break;
        case 6:
            elementsT2.emplace_back(id, &nodes, node_ids);
            elementsT2.back().qdata = &quadratures[1];
            elementsT2.back().qdata_line = &quadratures[5];
            break;
        case 9:
            elementsQ2.emplace_back(id, &nodes, node_ids);
            elementsQ2.back().qdata = &quadratures[3];
            elementsQ2.back().qdata_line = &quadratures[5];
            break;
        default:
            std::cerr<<"Unrecognized element type"<<std::endl;
            throw -1;
        }
    }

    inFile.close();

    // Initializing shape functions when necessary
    if(elementsT1.size() > 0){
        quadratures[0].initialize_shape_functions(elementsT1[0].n_nodes);
        quadratures[4].initialize_shape_functions_line(1);
    }
    if(elementsT2.size() > 0){
        quadratures[1].initialize_shape_functions(elementsT2[0].n_nodes);
        quadratures[5].initialize_shape_functions_line(2);
    }
    if(elementsQ1.size() > 0){
        quadratures[2].initialize_shape_functions(elementsQ1[0].n_nodes);
        quadratures[4].initialize_shape_functions_line(1);
    }
    if(elementsQ2.size() > 0){
        quadratures[3].initialize_shape_functions(elementsQ2[0].n_nodes);
        quadratures[5].initialize_shape_functions_line(2);
    }

     //Adding sentinels
    elementsT1.emplace_back();
    elementsT2.emplace_back();
    elementsQ1.emplace_back();
    elementsQ2.emplace_back();

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

    QuadData * qdataT1 = NULL;
    QuadData * qdataT2 = NULL;
    QuadData * qdataQ1 = NULL;
    QuadData * qdataQ2 = NULL;

    // Initializing quadratures at nodes when necessary
    if(elementsT1.size() > 1){
        int size = elementsT1[0].n_nodes;
        qdataT1 = new QuadData(size);
        qdataT1->initialize_shape_functions(size);
    }
    if(elementsT2.size() > 1){
        int size = elementsT2[0].n_nodes;
        qdataT2 = new QuadData(size);
        qdataT2->initialize_shape_functions(size);
    }
    if(elementsQ1.size() > 1){
        int size = elementsQ1[0].n_nodes;
        qdataQ1 = new QuadData(size);
        qdataQ1->initialize_shape_functions(size);
    }
    if(elementsQ2.size() > 1){
        int size = elementsQ2[0].n_nodes;
        qdataQ2 = new QuadData(size);
        qdataQ2->initialize_shape_functions(size);
    }

    // Calculating gradients

    for(T1_iterator E = T1ptr(); E->id >=0; E++){
        CALC_GRADIENT_LOCAL(E, qdataT1);
    }

    for(T2_iterator E = T2ptr(); E->id >=0; E++){
        CALC_GRADIENT_LOCAL(E, qdataT2);
    }

    for(Q1_iterator E = Q1ptr(); E->id >=0; E++){
        CALC_GRADIENT_LOCAL(E, qdataQ1);
    }

    for(Q2_iterator E = Q2ptr(); E->id >=0; E++){
        CALC_GRADIENT_LOCAL(E, qdataQ2);
    }

    gradients_calculated = true;

    // Removing pointers

    if(qdataT1 != NULL){
        delete qdataT1;
    }
    if(qdataT2 != NULL){
        delete qdataT2;
    }
    if(qdataQ1 != NULL){
        delete qdataQ1;
    }
    if(qdataQ2 != NULL){
        delete qdataQ2;
    }
}


T1_iterator Domain::T1ptr(){
    return elementsT1.begin();
}

T2_iterator Domain::T2ptr(){
    return elementsT2.begin();
}

Q1_iterator Domain::Q1ptr(){
    return elementsQ1.begin();
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
   return -4 + elementsT1.size() + elementsQ2.size() +elementsT2.size() + elementsQ1.size();
}

void Domain::export_result_dat(Settings settings){

    std::ofstream outFile;
    outFile.open(settings.results_dat_filename);

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



void Domain::export_result_vtk(Settings settings){

    // Switching filename from std::string to char*
    int name_length = settings.results_vtk_filename.size();
    char filename[name_length+1]; // Just in case
    settings.results_vtk_filename.copy(filename, name_length);
    filename[name_length] = '\0'; //string copy fails to terminate with null character

    // Using FILE* instead of std::ofstream so we can use the fprintf function with it.
    FILE * outFile;
    outFile =fopen(filename, "w");

    // Header
    fprintf(outFile, "# vtk DataFile Version 1.0.\nRESULT\nASCII\n\n");
    fprintf(outFile, "DATASET UNSTRUCTURED_GRID\n\n");

    // Nodes
    fprintf(outFile, "POINTS %d float\n", (int) n_nodes());

    for(N_iterator n=Nptr(); n->id >= 0; n++){
        fprintf(outFile, "      %14.8E      %14.8E      %14.8E\n", n->coordinates[0], n->coordinates[1], 0.0);
    }


    // Connectivities
    int connect_table_size = n_elems()
                             + (elementsT1.size()-1) * elementsT1[0].n_nodes
                             + (elementsT2.size()-1) * elementsT2[0].n_nodes
                             + (elementsQ1.size()-1) * elementsQ1[0].n_nodes
                             + (elementsQ2.size()-1) * elementsQ2[0].n_nodes; // TODO:  add more element types

    fprintf(outFile, "\n");
    fprintf(outFile, "CELLS %6d %6d\n", (int) n_elems(), connect_table_size);

    char buffer[1024];

    for(T1_iterator E = T1ptr(); E->id >= 0; E++){
        E->connectivity_line_vtk(buffer);
        fprintf(outFile, "%s", buffer);
    }
    for(T2_iterator E = T2ptr(); E->id >= 0; E++){
        E->connectivity_line_vtk(buffer);
        fprintf(outFile, "%s", buffer);
    }
    for(Q1_iterator E = Q1ptr(); E->id >= 0; E++){
        E->connectivity_line_vtk(buffer);
        fprintf(outFile, "%s", buffer);
    }
    for(Q2_iterator E = Q2ptr(); E->id >= 0; E++){
        E->connectivity_line_vtk(buffer);
        fprintf(outFile, "%s", buffer);
    }

    fprintf(outFile, "\n");

    // Element types

    fprintf(outFile, "CELL_TYPES %d\n", (int) n_elems());

    std::string elem_types = "";

    for(T1_iterator E = T1ptr(); E->id >= 0; E++){
        fprintf(outFile, "% 2d", E->vtk_id);
    }
    for(T2_iterator E = T2ptr(); E->id >= 0; E++){
        fprintf(outFile, "% 2d", E->vtk_id);
    }
    for(Q1_iterator E = Q1ptr(); E->id >= 0; E++){
        fprintf(outFile, "% 2d", E->vtk_id);
    }
    for(Q2_iterator E = Q2ptr(); E->id >= 0; E++){
        fprintf(outFile, "% 2d", E->vtk_id);
    }

    // Potential field
    fprintf(outFile,"\n\n");
    fprintf(outFile,"POINT_DATA %d\n", (int) n_nodes());
    fprintf(outFile,"SCALARS Potential float\n");
    fprintf(outFile,"LOOKUP_TABLE default\n");

    for(N_iterator N = Nptr(); N->id >=0; N++){
        fprintf(outFile, "%f\n", N->u);
    }


    // Velocity field
    fprintf(outFile,"VECTORS Velocity float\n"); // Not printed in Matlab code
//    fprintf(outFile,"LOOKUP_TABLE default\n");

    for(N_iterator N = Nptr(); N->id >=0; N++){
        fprintf(outFile, "%10f   %10f   %10f\n", N->grad_u(0), N->grad_u(1), 0.0);
    }

}



































