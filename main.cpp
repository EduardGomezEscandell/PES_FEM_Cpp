#include <iostream>
#include <stdlib.h> // atoi
#include <stdio.h>  // fprintf

#include "dependencies/Eigen/Dense"
#include "dependencies/Eigen/Sparse"

#include "quaddata.h"
#include "domain.h"
#include "systemofequations.h"
#include "settings.h"

typedef Eigen::SparseMatrix<double> SpMat; // Typedef'ing sparse matrices

int main(int argc, char** argv)
{    
    Settings settings(argc, argv);
    if(settings.only_help){
        // Displayed help text. Aborting execution.
        return 0;
    }

    int n_points = 5;
    if(argc>1){
        n_points = atoi(argv[1]);
    }
    std::cout<<"Loading data ..."<<std::endl;
    // Loading quadrature
    QuadData qdata_at_corners(3);
    QuadData qdata(settings.gauss_filename, n_points);

    // Loading geometry
    Domain domain(settings);

    // Loading boundary conditions
    SystemOfEquations SysEq;
    SysEq.load_bc(&domain, settings.boco_filename);

    // Loading shape functions
    std::cout<<"Preliminary math ..."<<std::endl;
    qdata.initialize_shape_functions(domain.elementsT1[0].n_nodes);

    // Assembling
    std::cout<<"Assembling system of equations..."<<std::endl;
    SysEq.assemble(&domain, &qdata);
//    SysEq.plot_sparsity(print_file);

    // Solving
    std::cout<<"Solving..."<<std::endl;
    double error = SysEq.solve(&domain);
    std::cout<<"System solved with a residual norm of "<<error<<std::endl;

    // Obtaining gradients
    domain.calc_gradients(qdata_at_corners);

    // Storing results
    domain.export_result(settings.results_filename);
}
