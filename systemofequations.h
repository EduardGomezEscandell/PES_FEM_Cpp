#ifndef SYSTEMOFEQUATIONS_H
#define SYSTEMOFEQUATIONS_H

#include <vector>

#include "Eigen/Sparse"
#include "Eigen/Dense"

#include "domain.h"
#include "quaddata.h"

typedef Eigen::SparseMatrix<double> SpMat; // Typedef'd sparse matrices
typedef Eigen::SparseVector<double> SpVec; // Typedef'd sparse vectors
typedef std::vector<Eigen::Triplet<double>> cooMat; //Typedef'd COO matrix

class SystemOfEquations
{
public:
    cooMat K_coo;

    SpMat K;
    SpVec F;
    SpVec U;

    SystemOfEquations();
    void assemble_K(Domain dom, QuadData qdata);
};

#endif // SYSTEMOFEQUATIONS_H
