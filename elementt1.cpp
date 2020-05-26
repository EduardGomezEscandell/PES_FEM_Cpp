#include "elementt1.h"

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
