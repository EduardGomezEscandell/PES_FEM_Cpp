#ifndef QUADDATA_H
#define QUADDATA_H
#include "quadpoint.h"
#include <vector>

class QuadData
{
public:
    QuadPoint* points;
    int npoints;
    QuadData(std::string filename, int n_points_requested);
protected:
    std::vector<std::string> split_string(std::string txt, char separator);
};

#endif // QUADDATA_H
