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
    Point(const Point& c_other);
    Point(Point&& c_other);
    Point();
    Point& operator=(const Point& c_other);
    Point& operator=(Point&& c_other);
    vector<double>& vecGetDimension();
    double dCalculateDistance(const Point& other);
private:
    const double d_Wrong_value=-1;
    std::vector<double> vec_dimension;
    void vCopy(const Point& c_other);
    void vCopyMove(Point& c_other);
};




#endif //POINT_H
