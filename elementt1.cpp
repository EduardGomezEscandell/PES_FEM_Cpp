#include "elementt1.h"
#include <stdlib.h>

ElementT1::ElementT1(int element_id, Node* node_list, int *node_ids) : Element(element_id,node_list, node_ids)
{

}

double ElementT1::get_area(){
    double ** X = Element::get_coordinates();
    double u[2];
    double v[2];
    for(int i=0; i<2; i++){
        u[i] = X[1][i] - X[0][i];
        v[i] = X[2][i] - X[0][i];
    }
    double area = 0.5*(u[0]*v[1] - u[1]*v[0]);
    return area;
}

double* ElementT1::barycentric_to_cartesian(double L1, double L2, double L3){
    // Returns a ponter to the coordinates in cartesian. Remember to free the pointer afterwards!
    static double * cartesian = (double *) malloc(3 * sizeof(double));
    for(int i=0; i<3; i++){
        cartesian[i] = L1 * Element::nodes[0].coordinates[i]
                     + L2 * Element::nodes[1].coordinates[i]
                     + L3 * Element::nodes[2].coordinates[i];
    }
    return cartesian;
}

double *ElementT1::barycentric_to_cartesian(double *L){
    return ElementT1::barycentric_to_cartesian(L[0], L[1], L[2]);
}

void ElementT1::initialize_shape_functions(QuadData *qdata){
    for(int i=0; i<qdata->npoints; i++){
        double x = qdata->points[i].coordinates[0];
        double y = qdata->points[i].coordinates[1];

        // Shape functions
        qdata->points[i].N = Eigen::MatrixXi(1, Element::n_nodes);

        qdata->points[i].N(0) = 1 - x - y;
        qdata->points[i].N(1) = x;
        qdata->points[i].N(2) = y;

        // Gradient
        qdata->points[i].gradN = Eigen::MatrixXi(2, Element::n_nodes);
        // N1
        qdata->points[i].gradN(0,0) = -1;
        qdata->points[i].gradN(1,0) = -1;
        // N2
        qdata->points[i].gradN(0,0) =  1;
        qdata->points[i].gradN(1,0) =  0;
        // N3
        qdata->points[i].gradN(0,0) =  0;
        qdata->points[i].gradN(1,0) =  1;
    }
}
