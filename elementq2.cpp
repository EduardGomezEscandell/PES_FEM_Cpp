#include "elementq2.h"

ElementQ2::ElementQ2() : Element()
{
    // Invalid element to use as sentinel
}


ElementQ2::ElementQ2(int element_id, std::vector<Node> * node_list, std::vector<int> node_ids) : Element(element_id,node_list, node_ids, 9)
{

}
