#include "elementt1.h"
#include <stdlib.h>

ElementT1::ElementT1() : Element()
{
    // Invalid element to use as sentinel
}

ElementT1::ElementT1(int element_id, Node* node_list, int* node_ids) : Element(element_id,node_list, node_ids, 3)
{

}

double *ElementT1::barycentric_to_cartesian(double *L){
    // Returns a ponter to the coordinates in cartesian. Remember to free the pointer afterwards!
    static double * cartesian = (double *) malloc(3 * sizeof(double));
    double L2 = 1 - L[0] - L[1];
    for(int i=0; i<3; i++){
        cartesian[i] = L[0] * Element::nodes[0]->coordinates[i]
                     + L[1] * Element::nodes[1]->coordinates[i]
                     +  L2  * Element::nodes[2]->coordinates[i];
    }
    return cartesian;
}

#define _X0_ nodes[0]->coordinates[0]
#define _X1_ nodes[1]->coordinates[0]
#define _X2_ nodes[2]->coordinates[0]

#define _Y0_ nodes[0]->coordinates[1]
#define _Y1_ nodes[1]->coordinates[1]
#define _Y2_ nodes[2]->coordinates[1]

Eigen::Matrix2d ElementT1::calc_jacobian(){

    jacobian(0,0) = _X1_ - _X0_;
    jacobian(0,1) = _Y1_ - _Y0_;

    jacobian(1,0) = _X2_ - _X0_;
    jacobian(1,1) = _Y2_ - _Y0_;

    jacobian_is_calculated = true;

    invJacobian = jacobian.inverse();

    area = jacobian.determinant();

    return jacobian;
}

void ElementT1::assemble(cooMat * K, QuadData *qdata){
    calc_jacobian();

    Eigen::Matrix3d k_local;

    k_local <<0, 0, 0,
              0, 0, 0,
              0, 0, 0;

    for(QuadPoint *q=qdata->points; q->w >= 0; q++){
        Eigen::MatrixXd gradN;
        gradN = invJacobian * q->gradN;

        k_local += q->w * (gradN.transpose() * gradN);
    }

    k_local *= area / qdata->total_weight;

    for(int i=0; i<n_nodes; i++){
        for(int j=0; j<n_nodes; j++){
            K->emplace_back(nodes[i]->id, nodes[j]->id, k_local(i,j));
        }
    }
}
