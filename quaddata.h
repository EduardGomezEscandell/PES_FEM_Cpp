#ifndef QUADDATA_H
#define QUADDATA_H

#include <fstream> // ifstream
#include <stdlib.h> // stoi
#include <vector>

#include "aux_functions.h" // split_string, barycentric_to_cartesian
#include "quadpoint.h"
#include "elementt1.h"
// #include "elementt2.h"
// #include "elementq1.h"
// #include "elementq2.h"

class QuadData
{
public:
    QuadPoint* points;
    int npoints;
    double total_weight;
    QuadData(std::string filename, int n_points_requested);
    void square_quadrature();
    void initialize_shape_functions(ElementT1 sample_element);
    /* TODO
    void initialize_shape_functions(ElementT2 sample_element);
    void initialize_shape_functions(ElementQ1 sample_element);
    void initialize_shape_functions(ElementQ2 sample_element);
    */
};

#endif // QUADDATA_H
