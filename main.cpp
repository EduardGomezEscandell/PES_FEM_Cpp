#include <iostream>
#include <stdlib.h> // atoi
#include <stdio.h>  // fprintf

#include "dependencies/Eigen/Dense"
#include "dependencies/Eigen/Sparse"

#include "quaddata.h"
#include "domain.h"
#include "systemofequations.h"

typedef Eigen::SparseMatrix<double> SpMat; // Typedef'ing sparse matrices

int main(int argc, char** argv)
{
    std::string gauss_filename = "../PES_FEM_Cpp/math_data/gauss_points_triangle.txt";
    std::string node_filename = "../PES_FEM_Cpp/mesh_data/PES_2D_tri_lin/Mesh5/Node_2D_tri_lin.dat";
    std::string mesh_filename = "../PES_FEM_Cpp/mesh_data/PES_2D_tri_lin/Mesh5/Element_2D_tri_lin.dat";
    std::string boco_filename = "../PES_FEM_Cpp/mesh_data/PES_2D_tri_lin/Mesh5/boundaries.dat";
    std::string print_file = "../PES_FEM_Cpp/results/here.pbm";
    std::string results_filename = "../PES_FEM_Cpp/mesh_data/PES_2D_tri_lin/Mesh5/result.dat";

    int n_points = 5;
    if(argc>1){
        n_points = atoi(argv[1]);
    }
    std::cout<<"Loading data ..."<<std::endl;
    // Loading quadrature
    QuadData qdata(gauss_filename, n_points);

    // Loading geometry
    Domain domain(node_filename, mesh_filename);

    // Loading boundary conditions
    SystemOfEquations SysEq;
    SysEq.load_bc(domain, boco_filename);

    // Loading shape functions
    std::cout<<"Preliminary math ..."<<std::endl;
    qdata.initialize_shape_functions(domain.elementsT1[0]);  

    // Assembling
    std::cout<<"Assembling system of equations..."<<std::endl;
    SysEq.assemble(domain, qdata);
//    SysEq.plot_sparsity(print_file);

    // Solving
    std::cout<<"Solving..."<<std::endl;
    double error = SysEq.solve();
    std::cout<<"System solved with a residual norm of "<<error<<std::endl;

    // Storing results
    SysEq.export_result(results_filename);

    //
}
