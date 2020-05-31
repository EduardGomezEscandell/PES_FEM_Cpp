#ifndef QUADDATA_H
#define QUADDATA_H

#include <fstream> // ifstream
#include <stdlib.h> // stoi
#include <vector>
#include <math.h> // sqrt

#include "aux_functions.h" // split_string, barycentric_to_cartesian
#include "quadpoint.h"
#include "settings.h"

typedef std::vector<QuadPoint>::iterator qiterator;

class QuadData
{
public:
    std::vector<QuadPoint> points;
    qiterator pointsptr();

    int npoints;
    double total_weight;

    QuadData copy();

    QuadData();
    QuadData(size_t n_nodes);
    QuadData(std::string filename, int n_points_requested);

    void square_quadrature();
    void initialize_shape_functions(int n_functions);
    void initialize_shape_functions_line(int n_functions);
protected:
    void initialize_shape_functions_tri_lin();
    void initialize_shape_functions_tri_quad();
    void initialize_shape_functions_quad_lin();
    void initialize_shape_functions_quad_quad();
};

QuadData * initialize_quadratures(Settings settings);

#endif // QUADDATA_H
