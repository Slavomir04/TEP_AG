//
// Created by Slawomir on 13.01.2025.
//
#include "CInvidual.h"

#include <stdexcept>


CInvidual::CInvidual(Evaluator *pc_evaluator,RandomGenerator* pc_random_generator) {
    if (pc_evaluator != nullptr && pc_random_generator != nullptr) {
        vFirstInit();
        this->pc_evaluator = pc_evaluator;
        this->pc_random_generator = pc_random_generator;
        vRandomInit();
    }else {
        vThrowInitError(str_init_error);
    }
}

CInvidual::CInvidual(Evaluator* pc_evaluator,RandomGenerator* pc_random_generator, vector<int> &vec_genotype) {
    if (pc_evaluator != nullptr && pc_random_generator != nullptr) {
        vFirstInit();
        this->pc_evaluator = pc_evaluator;
        this->pc_random_generator = pc_random_generator;
        this->vec_genotype = move(vec_genotype);
    }else {
        vThrowInitError(str_init_error);
    }
}

CInvidual::CInvidual(CInvidual &&c_other) {
    vFirstInit();
    vCopyMove(move(c_other));
}



CInvidual& CInvidual::operator=(const CInvidual&  c_other){
    vFirstInit();
    vCopy(c_other);
    return *this;
}
CInvidual& CInvidual::operator=(CInvidual&& c_other) {
    vFirstInit();
    vCopyMove(move(c_other));
    return *this;
}
void CInvidual::vMutation(double d_Treshold) {
    d_fitness = d_Wrong_value;
    uniform_int_distribution<int> c_distribution_point = uniform_int_distribution<int>(pc_evaluator->iGetLowBound(), pc_evaluator->iGetHighBound());
    for (int i=0; i<this->vec_genotype.size(); i++) {
        if (pc_random_generator->dGetRandomNumber(c_distribution_0_1)<d_Treshold) {
            vec_genotype[i] = pc_random_generator->iGetRandomNumber(c_distribution_point);
        }
    }
}

pair<CInvidual, CInvidual> CInvidual::paircCrossover(const CInvidual &c_other) {
    if (this->vec_genotype.size() == c_other.vec_genotype.size()) {
        CInvidual c_invidual_1;
        CInvidual c_invidual_2;

        c_invidual_1.pc_evaluator = this->pc_evaluator;
        c_invidual_1.pc_random_generator = this->pc_random_generator;
        c_invidual_1.vec_genotype.resize(this->vec_genotype.size());
        c_invidual_2.pc_evaluator = this->pc_evaluator;
        c_invidual_2.pc_random_generator = this->pc_random_generator;
        c_invidual_2.vec_genotype.resize(this->vec_genotype.size());

        int i_cross_index = pc_random_generator->iGetRandomNumber(pc_evaluator->iGetLowBound(), pc_evaluator->iGetHighBound());

        int index=0;
        while (index<i_cross_index) {
            c_invidual_1.vec_genotype[index] = vec_genotype[index];
            c_invidual_2.vec_genotype[index] = c_other.vec_genotype[index];
            index++;
        }
        while (index<pc_evaluator->iGetPointsCount()){
            c_invidual_1.vec_genotype[index] =  c_other.vec_genotype[index];
            c_invidual_2.vec_genotype[index] = vec_genotype[index];
            index++;
        }
        return pair<CInvidual,CInvidual>(move(c_invidual_1), move(c_invidual_2));
    }else {
        vThrowInitError(str_non_compatibility);
    }
}
pair<CInvidual,CInvidual> CInvidual::paircCrossover(CInvidual&& c_other) {
    if (this->vec_genotype.size() == c_other.vec_genotype.size()) {
        CInvidual c_invidual_1(move(*this));
        CInvidual c_invidual_2(move(c_other));

        c_invidual_1.d_fitness = d_Wrong_value;
        c_invidual_2.d_fitness = d_Wrong_value;

        int index = pc_random_generator->iGetRandomNumber(pc_evaluator->iGetLowBound(), pc_evaluator->iGetHighBound());

        int temp;
        while (index<pc_evaluator->iGetPointsCount()){
            temp = c_invidual_1.vec_genotype[index];
            c_invidual_1.vec_genotype[index] = c_invidual_2.vec_genotype[index];
            c_invidual_2.vec_genotype[index] = temp;
            index++;
        }
        return pair<CInvidual,CInvidual>(move(c_invidual_1), move(c_invidual_2));
    }else {
        vThrowInitError(str_non_compatibility);
    }
}

double CInvidual::dEvaluate() {
    if (d_fitness == d_Wrong_value) {
        d_fitness = pc_evaluator->dEvaluate(vec_genotype);
    }
    return d_fitness;
}

vector<int>& CInvidual::vecGetGenotype() {
    return vec_genotype;
}

CInvidual::CInvidual() {
    vFirstInit();
}

void CInvidual::vFirstInit() {
    c_distribution_0_1 = uniform_real_distribution<double>(0,1);
    d_fitness = d_Wrong_value;
}

void CInvidual::vRandomInit() {
    uniform_int_distribution<int> c_distribution_point = uniform_int_distribution<int>(pc_evaluator->iGetLowBound(),pc_evaluator->iGetHighBound());
    vec_genotype = vector<int>(pc_evaluator->iGetPointsCount());
    for (int i=0; i < vec_genotype.size(); i++) {
        vec_genotype[i] = pc_random_generator->iGetRandomNumber(c_distribution_point);
    }
}

void CInvidual::vCopy(const CInvidual &c_other) {
    pc_evaluator = c_other.pc_evaluator;
    pc_random_generator = c_other.pc_random_generator;
    vec_genotype = c_other.vec_genotype;
    d_fitness = c_other.d_fitness;
}

void CInvidual::vCopyMove(CInvidual &&c_other) {
    pc_evaluator = c_other.pc_evaluator;
    pc_random_generator = c_other.pc_random_generator;
    vec_genotype = move(c_other.vec_genotype);
    d_fitness = c_other.d_fitness;
    c_other.d_fitness = c_other.d_Wrong_value;
}

void CInvidual::vThrowInitError(const string& str_error) {
    throw runtime_error(str_error);
}
