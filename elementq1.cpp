#include "elementq1.h"

ElementQ1::ElementQ1() : Element()
{
    n_nodes = 4;
    // Invalid element to use as sentinel
}


ElementQ1::ElementQ1(int element_id, std::vector<Node> * node_list, std::vector<int> node_ids) : Element(element_id,node_list, node_ids, 4)
{

}

#define _X0_ nodes[0]->coordinates[0]
#define _X1_ nodes[1]->coordinates[0]
#define _X2_ nodes[2]->coordinates[0]
#define _X3_ nodes[3]->coordinates[0]

#define _Y0_ nodes[0]->coordinates[1]
#define _Y1_ nodes[1]->coordinates[1]
#define _Y2_ nodes[2]->coordinates[1]
#define _Y3_ nodes[3]->coordinates[1]



void ElementQ1::calc_jacobian(){
    // Jacobian is a linear combination J = J0 + [xi, eta]' J1

    jacobian_0(0,0) = - _X0_ + _X1_ + _X2_ - _X3_;
    jacobian_0(0,1) = - _Y0_ + _Y1_ + _Y2_ - _Y3_;

    jacobian_0(1,0) = - _X0_ - _X1_ + _X2_ + _X3_;
    jacobian_0(1,1) = - _Y0_ - _Y1_ + _Y2_ + _Y3_;

    jacobian_1(0) = + _X0_ - _X1_ + _X2_ - _X3_;
    jacobian_1(1) = - _Y0_ - _Y1_ + _Y2_ + _Y3_;

    area = jacobian_0.determinant(); //
}

Eigen::Matrix2d ElementQ1::get_jacobian(QuadPoint q){
    Eigen::Vector2d X;
    X << q.coordinates[0], q.coordinates[1];
    return jacobian_0 + X * jacobian_1.transpose();
}

Eigen::Matrix2d ElementQ1::get_invJacobian(QuadPoint q){
    return get_jacobian(q).inverse();
}

Edge ElementQ1::get_edge(int i){
    std::vector<int> node_ids = {i, (i+1)%n_nodes};
    Edge edge(node_ids, nodes, qdata_line);
    return edge;
}

