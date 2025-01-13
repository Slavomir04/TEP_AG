//
// Created by Slawomir on 13.01.2025.
//

#ifndef POINT_H
#define POINT_H
#include <vector>

using namespace std;
class Point {

public:
    Point(std::vector<double> vec_dimension);
    vector<double>& vecGetDimension();
    double dCalculateDistance(const Point& other);
private:
    const double d_Wrong_value=-1;
    std::vector<double> vec_dimension;
};



#endif //POINT_H
