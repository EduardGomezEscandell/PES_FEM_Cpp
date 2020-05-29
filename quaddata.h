#ifndef QUADDATA_H
#define QUADDATA_H

#include <fstream> // ifstream
#include <stdlib.h> // stoi
#include <vector>

#include "aux_functions.h" // split_string, barycentric_to_cartesian
#include "quadpoint.h"

typedef std::vector<QuadPoint>::iterator qiterator;

class QuadData
{
public:
    std::vector<QuadPoint> points;
    qiterator pointsptr();

    int npoints;
    double total_weight;

    QuadData(size_t n_nodes);
    QuadData(std::string filename, int n_points_requested);

    void square_quadrature();
    void initialize_shape_functions(int n_functions);
};

#endif // QUADDATA_H
