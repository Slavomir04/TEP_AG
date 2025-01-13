//
// Created by Slawomir on 13.01.2025.
//

#ifndef CINVIDUAL_H
#define CINVIDUAL_H

#include <vector>
#include <random>
#include "Evaluator.h"
#include "RandomGenerator.h"
using namespace std;
class CInvidual { //osobnik
public:
    CInvidual(Evaluator* pc_evaluator,RandomGenerator* pc_random_generator);
    CInvidual(Evaluator* pc_evaluator,RandomGenerator* pc_random_generator,vector<int>& vec_genotype);
    CInvidual(CInvidual&& c_other);
    CInvidual& operator=(const CInvidual& c_other);
    CInvidual& operator=(CInvidual&& c_other);


    void vMutation(double d_Treshold);
    pair<CInvidual,CInvidual> paircCrossover(const CInvidual& c_other);
    pair<CInvidual,CInvidual> paircCrossover(CInvidual&& c_other);
    double dEvaluate();
    vector<int>& vecGetGenotype();

private:
    CInvidual();
    const double d_Wrong_value = -1;
    const string str_init_error = "CInvidual init error";
    const string str_non_compatibility = "CInvidual, two inviduals are not compatibile";

    Evaluator* pc_evaluator;
    RandomGenerator* pc_random_generator;
    vector<int> vec_genotype;
    uniform_real_distribution<double> c_distribution_0_1;
    double d_fitness;
    //func
    void vFirstInit();
    void vRandomInit();
    void vCopy(const CInvidual& c_other);
    void vCopyMove(CInvidual&& c_other);
    void vThrowInitError(const string& str_error);
};




#endif //CINVIDUAL_H
