#include "elementq2.h"

ElementQ2::ElementQ2() : Element()
{
    n_nodes = 9;
    // Invalid element to use as sentinel
}


ElementQ2::ElementQ2(int element_id, std::vector<Node> * node_list, std::vector<int> node_ids) : Element(element_id,node_list, node_ids, 9)
{

}

Eigen::Matrix2d ElementQ2::calc_jacobian(){
    // TODO
}

Eigen::Matrix2d ElementQ2::get_jacobian(QuadPoint q){
    // TODO
}

Eigen::Matrix2d ElementQ2::get_invJacobian(QuadPoint q){
    // TODO
}

int ElementQ2::consecutive_node(int i){
    // TODO
}

Edge ElementQ2::get_edge(int i){
    // TODO

//    Edge edge(node_ids, nodes, qdata_line);
//    return edge;
}
