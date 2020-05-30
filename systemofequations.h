#ifndef SYSTEMOFEQUATIONS_H
#define SYSTEMOFEQUATIONS_H

#include <vector>

#include "dependencies/Eigen/Sparse"
#include "dependencies/Eigen/Dense"
#include "dependencies/Eigen/SparseCholesky"

#include "domain.h"
#include "quaddata.h"

typedef Eigen::SparseMatrix<double> SpMat;          // Typedef'd sparse matrices

class SystemOfEquations
{
public:
    cooMat K_coo;

    size_t size;
    double inv_penalty = 1e-6;

    SpMat K;
    Eigen::VectorXd F;
    Eigen::VectorXd U;

    std::vector<Node *> dirichlet_nodes;
    std::vector<Node *> neumann_nodes;

    SystemOfEquations();
    void assemble(Domain * dom, QuadData * qdata);
    void load_bc(Domain * dom, std::string filename);
    double solve();
    double solve(Domain * dom);
    void plot_sparsity(std::string filename);
    void calc_gradients(Domain * dom);
};


// Using macro so I don't need to use basically the same method for all four element types
#define ASSEMBLE_LOCAL(K_coo, E, qdata) do{                             \
    E->calc_jacobian();                                                    \
    Eigen::MatrixXd k_local = Eigen::MatrixXd::Zero(E->n_nodes, E->n_nodes);  \
    for(qiterator q=qdata->points.begin(); q->w >= 0; q++){             \
        Eigen::MatrixXd gradN;                                          \
        gradN = E->get_invJacobian() * q->gradN;                        \
        k_local += q->w * (gradN.transpose() * gradN);                  \
    }                                                                   \
    k_local *= E->area / qdata->total_weight;                           \
    for(int i=0; i<E->n_nodes; i++){                                    \
        for(int j=0; j<E->n_nodes; j++){                                \
            K_coo.emplace_back(E->nodes[i]->id, E->nodes[j]->id, k_local(i,j));  \
        }                                                               \
    }                                                                   \
}while(0)


#endif // SYSTEMOFEQUATIONS_H
