#include "systemofequations.h"


SystemOfEquations::SystemOfEquations()
{

}

void SystemOfEquations::assemble_K(Domain domain, QuadData qdata){
    K_coo.reserve(5 * domain.n_nodes); // Quick approximation

    for(ElementT1 *E = domain.elementsT1; E->id >=0; E++){

        Eigen::Matrix3d k_local;
        k_local <<0, 0, 0,
                  0, 0, 0,
                  0, 0, 0;

        for(QuadPoint *q=qdata.points; q->w >= 0; q++){
            Eigen::MatrixXd gradN;
            gradN = E->jacobian * q->gradN;

            k_local += q->w * (gradN.transpose() * gradN);

            for(int i=0; i<3; i++){
                for(int j=0; j<3; j++){
                    K_coo.emplace_back(E->nodes[i].id, E->nodes[j].id, k_local(i,j));
                }
            }
        }
    }
}
