#ifndef SYSTEMOFEQUATIONS_H
#define SYSTEMOFEQUATIONS_H

#include <vector>

#include "dependencies/Eigen/Sparse"
#include "dependencies/Eigen/Dense"
#include "dependencies/Eigen/SparseCholesky"

#include "domain.h"
#include "quaddata.h"

typedef Eigen::SparseMatrix<double> SpMat;          // Typedef'd sparse matrices
typedef std::vector<Eigen::Triplet<double>> cooMat; //Typedef'd COO matrix

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
    void assemble(Domain dom, QuadData qdata);
    void load_bc(Domain dom, std::string filename);
    double solve();
    void plot_sparsity(std::string filename);
    void export_result(std::string filename);
};

#endif // SYSTEMOFEQUATIONS_H
