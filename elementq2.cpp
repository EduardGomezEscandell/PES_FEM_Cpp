#include "elementq2.h"

ElementQ2::ElementQ2(int element_id, Node* node_list, int *node_ids) : Element(element_id,node_list, node_ids)
{

}

double ElementQ2::get_area(){
    double ** X = Element::get_coordinates();

    for(int i=0; i<4; i++){
        X[i][2] = 0;
    }

    Eigen::Matrix3d M1, M2;

    for(int i=0; i<3;i++){
        for(int j=0; j<3;j++){
            M1(i,j) = X[i][j];
            int k = i ? i>1 : 4;
            M2(i,j) = X[k][j];
        }
    }

    double area = 0.5*(M1.determinant() + M2.determinant());
    return area;
}
