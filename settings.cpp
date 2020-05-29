#include "settings.h"

Settings::Settings(int argc, char ** argv)
{
    switch (argc){
    /*
     *  ONE ARGUMENT
     */
        case 1:
            // Full default settings
            return;
    /*
     *  TWO ARGUMENTS
     */
        case 2:
            // Default quadrature, chosen file. -f option disabled
            if(argv[1][0] != '-'){
                read_mesh_coice(argv);
            }
            // Options:
            else {
                if(argv[1][1] == 'h'){
                    print_help();
                }
                else if (argv[1][1] == 'f') { // If the -f was enabled with only 1 argument, then there is an error
                    throw "The -f option requires three fields:\n$PES_FEM_Cpp -f <node file> <mesh file> <boundaries file>\n Run the -h command for more info.";
                }
                else{
                    throw "Unrecognized option. \n Run the -h command for more info.";
                }
            }
            break;
    /*
     *  THREE ARGUMENTS
     */
         case 3:
            // Default quadrature, chosen file. -f option disabled
            if(argv[1][0] != '-'){
                read_mesh_coice(argv);
                read_quadrature_choice(argv[2]);
            }
            // Options:
            else {
                if(argv[1][1] == 'h'){
                    print_help();
                }
                else if (argv[1][1] == 'f') { // If the -f was enabled with only 2 arguments, then there is an error
                    throw "The -f option requires three fields:\n$PES_FEM_Cpp -f <node file> <mesh file> <boundaries file>\n Run the -h command for more info.";
                }
                else{
                    throw "Unrecognized option. \n Run the -h command for more info.";
                }
            }
            break;
    /*
     *  FOUR ARGUMENTS
     */
        case 4:
            if(argv[1][0] != '-'){
                throw "Wrong number of arguments";
            }
            if(argv[1][1] == 'h'){
                print_help();
            }
            else if (argv[1][1] == 'f') {
                node_filename = argv[2];
                mesh_filename = argv[3];
                boco_filename = argv[4];
            }
            else{
                throw "Unrecognized option.\n Run the -h command for more info.";
            }
            break;
    /*
     *  FIVE ARGUMENTS
     */
        case 5:
            if(argv[1][0] != '-'){
                throw "Wrong number of arguments\n Run the -h command for more info.";
            }
            if(argv[1][1] == 'h'){
                print_help();
            }
            else if (argv[1][1] == 'f') {
                node_filename = argv[2];
                mesh_filename = argv[3];
                boco_filename = argv[4];
                read_quadrature_choice(argv[5]);
            }
            else{
                throw "Unrecognized option. \n Run the -h command for more info.";
            }
            break;
    /*
     *  SIX OR MORE ARGUMENTS
     */
        default:
            throw "Wrong number of arguments \n Run the -h command for more info.";
    }
}

void Settings::print_help(){
    // Help
    std::cout<<"HELP"<<std::endl;
    std::cout<<"Ways of running the program:"<<std::endl;
    std::cout<<"1.Run this program with no options to see a sample.\n  Default options are the same as\n  $PES_FEM_Cpp 5T1 3"<<std::endl;
    std::cout<<"2.Chose the mesh to be run:\n  $PES_FEM_Cpp <mesh number><element type><order>\n  Avaliable meshes: 1 through 5\n  Available types: Q, T\n  Available Orders: 1, 2"<<std::endl;
    std::cout<<"3.Chose the quadrature size:\n  $PES_FEM_Cpp <mesh number><element type><order> <quadrature>\n  Available quadratures: 1 to 99"<<std::endl;
    std::cout<<"4.Chose some other mesh file:\n $PES_FEM_Cpp -f <path_to_nodes> <path_to_elements> <path_to_boundaries>"<<std::endl;
    std::cout<<"5.Chose some other mesh file and quadrature:\n $PES_FEM_Cpp -f <path_to_nodes> <path_to_elements> <path_to_boundaries> <quadrature>"<<std::endl;
    only_help = true;
}

void Settings::read_mesh_coice(char ** argv){
    char mesh_no = argv[1][0];
    std::string elemType  = elemType_interpreter(argv[1][1]);
    std::string elemOrder = elemOrder_interpreter(argv[1][2]);
    directory = "../PES_FEM_Cpp/mesh_data/PES_2D_" + elemType + "_" + elemOrder + "/Mesh" + mesh_no +"/";
    mesh_filename = directory + "Element_2D_" + elemType + "_" + elemOrder + ".dat";
    node_filename = directory +    "Node_2D_" + elemType + "_" + elemOrder + ".dat";
    boco_filename = directory + "boundaries.dat";
    results_filename= directory + "result.dat";
}

void Settings::read_quadrature_choice(char * raw){
    quadrature = std::stoi(raw);
}

std::string Settings::elemType_interpreter(char raw){
    switch(raw){
        case 'T':
            return "tri";
        case 'Q':
            return "quad";
        default:
            throw "Unrecognized element type. Try T or Q.";
    }
}

std::string Settings::elemOrder_interpreter(char raw){
    switch(raw){
        case '1':
            return "lin";
        case '2':
            return "quad";
        default:
            throw "Unrecognized element order. Try 1 or 2.";
    }
}
