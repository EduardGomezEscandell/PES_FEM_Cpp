#include "elementq2.h"

ElementQ2::ElementQ2(int element_id, Node* node_list, int *node_ids) : Element(element_id,node_list, node_ids)
{

}

double ElementQ2::get_area(){
    double ** X = Element::get_coordinates();



    return area;
}
