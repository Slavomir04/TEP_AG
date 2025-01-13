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
    double dEvaluate(vector<int> vec_genotype);
    int iGetPointsCount();
    int iGetLowBound();
    int iGetHighBound();
    int iGetNumGroups();

    private:
    vector<Point> vec_points;
private:
    const double d_Wrong_value = -1;
    mt19937 c_random_engine;

    const int i_low_bound;
    const int i_high_bound;
};



#endif //EVALUATOR_H
