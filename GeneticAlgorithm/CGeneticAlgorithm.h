//
// Created by Slawomir on 13.01.2025.
//

#ifndef CGENETICALGORITHM_H
#define CGENETICALGORITHM_H

#include <vector>
#include "CInvidual.h"
#include <float.h>
#include <iostream>
#include <stdexcept>

using namespace std;
class CGeneticAlgorithm {
public:
    CGeneticAlgorithm(Evaluator* evaluator);
    void run();
    CInvidual cGetBestIndividual();
private:
    const double d_mut_probability = 0.1;
    const double d_cross_probability = 0.5;
    const double d_run_time_sec = 10.0;
    bool b_initalised;

    int i_population; //musi być parzysta
    Evaluator* evaluator;
    //random
    RandomGenerator c_random_generator;
    uniform_int_distribution<int> c_distribution_point;
    uniform_real_distribution<double> c_distribution_0_1;

    //variables
    double d_best_fitness;
    CInvidual c_best_individual;
    vector<CInvidual> vec_population;

    //func
    void vThrowError(const string& str_error);
    void vEvaluate();
    void vCross();
    void vMutate();
};



#endif //CGENETICALGORITHM_H
