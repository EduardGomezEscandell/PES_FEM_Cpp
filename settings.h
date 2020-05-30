#ifndef SETTINGS_H
#define SETTINGS_H

#include <string>
#include <iostream>
#include <stdlib.h>

class Settings
{
public:

    std::string directory = "../PES_FEM_Cpp/mesh_data/PES_2D_tri_lin/Mesh1/";
    std::string gauss_filename = "../PES_FEM_Cpp/math_data/gauss_points_triangle.txt";
    std::string node_filename = "../PES_FEM_Cpp/mesh_data/PES_2D_tri_lin/Mesh1/Node_2D_tri_lin.dat";
    std::string mesh_filename = "../PES_FEM_Cpp/mesh_data/PES_2D_tri_lin/Mesh1/Element_2D_tri_lin.dat";
    std::string boco_filename = "../PES_FEM_Cpp/mesh_data/PES_2D_tri_lin/Mesh1/boundaries.dat";
    std::string results_dat_filename = "../PES_FEM_Cpp/mesh_data/PES_2D_tri_lin/Mesh1/result.dat";
    std::string results_vtk_filename = "../PES_FEM_Cpp/mesh_data/PES_2D_tri_lin/Mesh1/result.vtk";

    int quadrature = 1;
    bool only_help = false;


    Settings(int argc, char ** argv);
protected:
    std::string elemType_interpreter(char raw);
    std::string elemOrder_interpreter(char raw);
    void read_quadrature_choice(char * raw);
    void read_mesh_coice(char ** argv);
    void print_help();
};

#endif // SETTINGS_H
