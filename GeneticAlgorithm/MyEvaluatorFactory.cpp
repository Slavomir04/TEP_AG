//
// Created by Slawomir on 15.01.2025.
//

#include "MyEvaluatorFactory.h"

#include "RandomGenerator.h"

MyEvaluatorFactory::MyEvaluatorFactory(int i_points,int i_dims,double i_range,int i_groups) {
    this->i_points = i_points>=0 ? i_points : -i_points;
    this->i_dims = i_dims>=0 ? i_dims : -i_dims;
    this->i_range=i_range>=0 ? i_range : -i_range;
    this->i_groups=i_groups>=0 ? i_groups : -i_groups;

    RandomGenerator c_random_generator;

    vec_points.resize(this->i_points);
    for (int i = 0; i < this->i_points; i++) {
        vector<double> vec_dimensions(i_dims);
        for (int j = 0; j < i_dims; j++) {
            vec_dimensions[j]=c_random_generator.dGetRandomNumber(0,i_range);
        }
        vec_points[i] = Point(vec_dimensions);
    }

}

Evaluator * MyEvaluatorFactory::createEvaluator() {
    Evaluator* pc_result = new Evaluator(vec_points,i_groups);
    return pc_result;
}
