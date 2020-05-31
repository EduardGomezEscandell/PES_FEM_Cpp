#include "elementt2.h"

ElementT2::ElementT2() : Element()
{
    n_nodes = 6;
    // Invalid element to use as sentinel
}

ElementT2::ElementT2(int element_id, std::vector<Node> * node_list, std::vector<int> node_ids) : Element(element_id,node_list, node_ids, 3)
{

}


Eigen::Matrix2d ElementT2::calc_jacobian(){
    // TODO
}

Eigen::Matrix2d ElementT2::get_jacobian(QuadPoint q){
    // TODO
}

Eigen::Matrix2d ElementT2::get_invJacobian(QuadPoint q){
    // TODO
}

Edge ElementT2::get_edge(int i){
    // TODO

//    Edge edge(node_ids, nodes, qdata_line);
//    return edge;
}
