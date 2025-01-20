//
// Created by Slawomir on 13.01.2025.
//

#ifndef CGENETICALGORITHM_H
#define CGENETICALGORITHM_H

#include <vector>
#include "CInvidual.h"
#include <iostream>
#include <chrono>
#include <float.h>
using namespace std;
class CGeneticAlgorithm {
public:
    CGeneticAlgorithm(NGroupingChallenge::CGroupingEvaluator& evaluator);
    void vInitilized();
    void vRun();
    vector<int> vecGetBestSolution();
    double dGestBestFitness();
    void vSetMutationProbability(double d_new_probability);
    void vSetCrossoverProbability(double d_new_probability);
    void vSetRunTime(double d_time_seconds);
    void vSetEvenPopulationSize(int i_new_size);
private:
    const int i_wrong_value = -1;
    double d_mut_probability = 0.1;
    double d_cross_probability = 0.5;
    double d_run_time_sec = 10.0;
    int i_population = 10; //musi być parzysta
    NGroupingChallenge::CGroupingEvaluator evaluator;

    //random
    RandomGenerator c_random_generator;
    uniform_int_distribution<int> c_distribution_invidual;
    uniform_real_distribution<double> c_distribution_0_1;

    //variables
    double d_best_fitness;
    CInvidual c_best_individual;
    vector<CInvidual> vec_population;

    //func
    void vEvaluate();
    void vCross();
    void vMutate();
    void vCheckBest(CInvidual& c_invidual);
    void vFillPopulationRandom();
    void vReset();
    int iGetParents(int i_candidate_a,int i_candidate_b);
    std::chrono::high_resolution_clock::time_point timeGetCurrentTime();

};



#endif //CGENETICALGORITHM_H
