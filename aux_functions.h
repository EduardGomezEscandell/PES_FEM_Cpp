#ifndef AUX_FUNCTIONS_H
#define AUX_FUNCTIONS_H

#include <string>
#include <vector>
//#include "Eigen/Sparse"

//typedef Eigen::SparseMatrix<double> SpMat; // Typedef'ing sparse matrices

std::vector<std::string> split_string(std::string txt, char separator);
double *barycentric_to_cartesian(double *L, double corners[3][2]);

#endif
