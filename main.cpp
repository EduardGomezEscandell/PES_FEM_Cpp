#include <iostream>
#include <stdlib.h> // atoi
#include <stdio.h>  // fprintf

#include "quaddata.h"
#include "domain.h"
#include "Eigen/Dense"
#include "Eigen/Sparse"

typedef Eigen::SparseMatrix<double> SpMat; // Typedef'ing sparse matrices

int main(int argc, char** argv)
{
    std::string gauss_filename = "../PES_FEM_Cpp/math_data/gauss_points_triangle.txt";
    std::string node_filename = "../PES_FEM_Cpp/mesh_data/PES_2D_tri_lin/Mesh1/Node_2D_tri_lin.dat";
    std::string mesh_filename = "../PES_FEM_Cpp/mesh_data/PES_2D_tri_lin/Mesh1/Element_2D_tri_lin.dat";

    int n_points = 5;
    if(argc>1){
        n_points = atoi(argv[1]);
    }
    // Loading quadarture
    QuadData qdata(gauss_filename, n_points);

    // Loading geometry
    Domain domain(node_filename, mesh_filename);

    // Loading shape functions
    qdata.initialize_shape_functions(domain.elementsT1[0]);

    // Pre-calculationg jacobians
    for(ElementT1 *E = domain.elementsT1; E->id >=0; E++){
        E->calc_jacobian();
    }

    // Assembling



}
