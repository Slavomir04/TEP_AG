//
// Created by Slawomir on 13.01.2025.
//

#ifndef EVALUATOR_H
#define EVALUATOR_H
#include <vector>
#include <random>
#include "Point.h"
using namespace std;
class Evaluator {
public:
    Evaluator(vector<Point> vec_points,int i_groups);
    double dEvaluate(vector<int>& vec_genotype);
    int iGetPointsCount();
    int iGetLowBound();
    int iGetHighBound();
    int iGetNumGroups();

    private:
    vector<Point> vec_points;
private:
    const double d_Wrong_value = -1;
    const int i_groups_count;
};



#endif //EVALUATOR_H
