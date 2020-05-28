#include "elementt1.h"
#include <stdlib.h>

ElementT1::ElementT1() : Element()
{
    // Invalid element to use as sentinel
}

ElementT1::ElementT1(int element_id, Node* node_list, int* node_ids) : Element(element_id,node_list, node_ids, 3)
{

}

double ElementT1::get_area(){
    if(!jacobian_is_calculated){
        calc_jacobian();
    }
    return jacobian.determinant();
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

#define _X0_ nodes[0].coordinates[0]
#define _X1_ nodes[1].coordinates[0]
#define _X2_ nodes[2].coordinates[0]

#define _Y0_ nodes[0].coordinates[1]
#define _Y1_ nodes[1].coordinates[1]
#define _Y2_ nodes[2].coordinates[1]

Eigen::Matrix2d ElementT1::calc_jacobian(){

    jacobian(0,0) = _X1_ - _X0_;
    jacobian(0,1) = _Y1_ - _Y0_;

    jacobian(1,0) = _X2_ - _X0_;
    jacobian(1,1) = _Y2_ - _Y0_;

    jacobian_is_calculated = true;

    return jacobian;
}
