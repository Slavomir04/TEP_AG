//
// Created by Slawomir on 13.01.2025.
//
#include "CInvidual.h"
#include <iostream>
#include <stdexcept>


CInvidual::CInvidual(Evaluator *pc_evaluator,RandomGenerator* pc_random_generator) {
    if (pc_evaluator != nullptr && pc_random_generator != nullptr) {
        vFirstInit();
        this->pc_evaluator = pc_evaluator;
        this->pc_random_generator = pc_random_generator;
        vRandomInit();
    }else {
        vThrowError(str_init_error);
    }
}

CInvidual::CInvidual(Evaluator* pc_evaluator,RandomGenerator* pc_random_generator, vector<int> &vec_genotype) {
    if (pc_evaluator != nullptr && pc_random_generator != nullptr) {
        vFirstInit();
        this->pc_evaluator = pc_evaluator;
        this->pc_random_generator = pc_random_generator;
        this->vec_genotype = move(vec_genotype);
    }else {
        vThrowError(str_nullptr);
    }
}

CInvidual::CInvidual(CInvidual &&c_other) {
    vFirstInit();
    vCopyMove(move(c_other));
}

CInvidual::CInvidual(const CInvidual &c_other) {
    vFirstInit();
    vCopy(c_other);
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
void CInvidual::vMutation(double d_probability) {
    if (pc_evaluator != nullptr && pc_random_generator != nullptr) {
        d_fitness = d_Wrong_value;
        uniform_int_distribution<int> c_distribution_point = uniform_int_distribution<int>(pc_evaluator->iGetLowBound(), pc_evaluator->iGetHighBound());
        for (int i=0; i<this->vec_genotype.size(); i++) {
            if (pc_random_generator->dGetRandomNumber(c_distribution_0_1)<d_probability) {
                vec_genotype[i] = pc_random_generator->iGetRandomNumber(c_distribution_point);
            }
        }
    }else {
        vThrowError(str_nullptr);
    }
}

pair<CInvidual, CInvidual> CInvidual::paircCrossover(const CInvidual &c_other) {
    if (pc_evaluator != nullptr && pc_random_generator != nullptr) {
        if (this->vec_genotype.size() == c_other.vec_genotype.size() && this->vec_genotype.size() > 1) {

            CInvidual c_new_1(*this);
            CInvidual c_new_2(c_other);

            int index = pc_random_generator->iGetRandomNumber(0, this->vec_genotype.size()-2);
            while (index < this->vec_genotype.size()) {
                c_new_1.vec_genotype[index] = c_other.vec_genotype[index];
                c_new_2.vec_genotype[index] = vec_genotype[index];
                index++;
            }

            return make_pair(c_new_1, c_new_2);
        }else if (this->vec_genotype.size() != c_other.vec_genotype.size()){
            vThrowError(str_non_compatibility);
        }
    }else {
        vThrowError(str_nullptr);
    }
}


double CInvidual::dEvaluate() {
    if (pc_evaluator!=nullptr) {
        if (d_fitness == d_Wrong_value) {
            d_fitness = pc_evaluator->dEvaluate(vec_genotype);
        }
        return d_fitness;
    } else vThrowError(str_nullptr);
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
    pc_evaluator = nullptr;
    pc_random_generator = nullptr;
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
    c_other.pc_evaluator = nullptr;
    c_other.pc_random_generator = nullptr;
}

void CInvidual::vThrowError(const string& str_error) {
    throw runtime_error(str_error);
}
