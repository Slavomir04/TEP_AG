//
// Created by Slawomir on 15.01.2025.
//

#ifndef CEVALUATORFACTORY_H
#define CEVALUATORFACTORY_H
#include "Evaluator.h"


class MyEvaluatorFactory {
public:
    MyEvaluatorFactory(int i_points,int i_dims,double i_range,int i_groups);
    Evaluator* createEvaluator();
private:
    vector<Point> vec_points;

    int i_points;
    int i_groups;
    double i_range;
    int i_dims;
};



#endif //CEVALUATORFACTORY_H
