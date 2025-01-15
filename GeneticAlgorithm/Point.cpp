//
// Created by Slawomir on 13.01.2025.
//

#include "Point.h"

#include <math.h>

Point::Point(std::vector<double> vec_dimension) : vec_dimension(vec_dimension){
}

Point::Point(const Point &c_other) {
    vCopy(c_other);
}

Point::Point(Point &&c_other) {
    vCopyMove(c_other);
}

Point::Point() {
}

Point & Point::operator=(const Point &c_other) {
    vCopy(c_other);
    return *this;
}

Point & Point::operator=(Point &&c_other) {
    vCopyMove(c_other);
    return *this;
}


vector<double>& Point::vecGetDimension() {
    return vec_dimension;
}

double Point::dCalculateDistance(const Point &other) {
    double d_distance = 0;
    if (vec_dimension.size() == other.vec_dimension.size()) {
        for (int i=0; i<vec_dimension.size(); i++) {
            d_distance += pow(vec_dimension[i] - other.vec_dimension[i], 2);
        }
        d_distance = sqrt(d_distance);
    }else {
        d_distance = d_Wrong_value;
    }
    return d_distance;
}

void Point::vCopy(const Point& c_other) {
    vec_dimension = c_other.vec_dimension;
}


void Point::vCopyMove(Point& c_other) {
    vec_dimension = move(c_other.vec_dimension);
}