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

double *ElementT1::barycentric_to_cartesian(double *L){
    // Returns a ponter to the coordinates in cartesian. Remember to free the pointer afterwards!
    static double * cartesian = (double *) malloc(3 * sizeof(double));
    double L2 = 1 - L[0] - L[1];
    for(int i=0; i<3; i++){
        cartesian[i] = L[0] * Element::nodes[0].coordinates[i]
                     + L[1] * Element::nodes[1].coordinates[i]
                     +  L2  * Element::nodes[2].coordinates[i];
    }
    return cartesian;
}
