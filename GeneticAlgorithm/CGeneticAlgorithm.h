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
#include <ctime>
using namespace std;
class CGeneticAlgorithm {
public:
    CGeneticAlgorithm(Evaluator* pc_evaluator);
    void run();
private:
    const string str_init_error = "init error";
    const double d_mut_probability = 0.1;
    const double d_cross_probability = 0.5;

    int i_population; //musi być parzysta
    Evaluator* evaluator;
    mt19937 c_random_engine;
    uniform_real_distribution<double> c_distribution_0_1;
    uniform_int_distribution<int> c_distribution_population;
    double d_best_fitness;
    CInvidual* c_best_individual;
    vector<CInvidual> vec_population;

    //func
    void vThrowInitError();
    void vEvaluate();
    void vCross();
    void vMutate();
};



#endif //CGENETICALGORITHM_H
