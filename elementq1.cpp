#include "elementq1.h"

ElementQ1::ElementQ1() : Element()
{
    // Invalid element to use as sentinel
}


ElementQ1::ElementQ1(int element_id, std::vector<Node> * node_list, std::vector<int> node_ids) : Element(element_id,node_list, node_ids, 9)
{

}


//Eigen::Matrix2d calc_jacobian(){

//}

//Eigen::Matrix2d get_jacobian(){

//}

//Eigen::Matrix2d get_invJacobian(){

//}
