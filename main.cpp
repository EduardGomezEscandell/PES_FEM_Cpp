#include <iostream>
#include <stdlib.h> // atoi
#include <stdio.h>  // fprintf

#include "dependencies/Eigen/Dense"
#include "dependencies/Eigen/Sparse"

#include "quaddata.h"
#include "domain.h"
#include "systemofequations.h"
#include "settings.h"

int main(int argc, char** argv)
{
    Settings settings(argc, argv);
    if(settings.only_help){
        // Displayed help text. Nothing to calculate.
        return 0;
    }

    std::cout<<"Loading data ..."<<std::endl;
    // Loading quadrature
    QuadData * qdata = initialize_quadratures(settings);

    // Loading geometry, calculating shape functions
    Domain domain(settings, qdata);

    // Loading boundary conditions
    SystemOfEquations SysEq;
    SysEq.load_bc(&domain, settings);

    // Assembling
    std::cout<<"Assembling system of equations..."<<std::endl;
    SysEq.assemble(&domain);
    SysEq.plot_sparsity(settings);

    // Solving
    std::cout<<"Solving..."<<std::endl;
    double error = SysEq.solve(&domain);
    std::cout<<"System solved with a residual norm of "<<error<<std::endl;

    // Obtaining gradients
    domain.calc_gradients();

    // Storing results
    domain.export_result_dat(settings);
    domain.export_result_vtk(settings);
}
