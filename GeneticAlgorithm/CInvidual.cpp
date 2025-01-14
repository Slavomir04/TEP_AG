//
// Created by Slawomir on 13.01.2025.
//
#include "CInvidual.h"
#include <iostream>
#include <stdexcept>


CInvidual::CInvidual(Evaluator *pc_evaluator,RandomGenerator* pc_random_generator) {
    b_initilised = pc_evaluator != nullptr && pc_random_generator != nullptr;
    if (b_initilised) {
        vFirstInit();
        this->pc_evaluator = pc_evaluator;
        this->pc_random_generator = pc_random_generator;
        vRandomInit();
    }
}

CInvidual::CInvidual(Evaluator* pc_evaluator,RandomGenerator* pc_random_generator, vector<int> &vec_genotype) {
    b_initilised = pc_evaluator != nullptr && pc_random_generator != nullptr;
    if (b_initilised) {
        vFirstInit();
        this->pc_evaluator = pc_evaluator;
        this->pc_random_generator = pc_random_generator;
        this->vec_genotype = move(vec_genotype);
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
    if (b_initilised) {
        d_fitness = d_Wrong_value;
        uniform_int_distribution<int> c_distribution_point = uniform_int_distribution<int>(pc_evaluator->iGetLowBound(), pc_evaluator->iGetHighBound());
        for (int i=0; i<this->vec_genotype.size(); i++) {
            if (pc_random_generator->dGetRandomNumber(c_distribution_0_1)<d_probability) {
                vec_genotype[i] = pc_random_generator->iGetRandomNumber(c_distribution_point);
            }
        }
    }
}

pair<CInvidual, CInvidual> CInvidual::paircCrossover(const CInvidual &c_other) {
    pair<CInvidual, CInvidual> c_result;
    if (b_initilised && c_other.b_initilised && this->vec_genotype.size() == c_other.vec_genotype.size() && this->vec_genotype.size() > 1) {
            CInvidual c_new_1(*this);
            CInvidual c_new_2(c_other);

            int index = pc_random_generator->iGetRandomNumber(0, this->vec_genotype.size()-2);
            while (index < this->vec_genotype.size()) {
                c_new_1.vec_genotype[index] = c_other.vec_genotype[index];
                c_new_2.vec_genotype[index] = vec_genotype[index];
                index++;
            }

          c_result = make_pair(c_new_1, c_new_2);
    }else {
       c_result = make_pair(c_other, c_other);
    }
    return c_result;
}


double CInvidual::dEvaluate() {
    if (b_initilised) {
        if (d_fitness == d_Wrong_value) {
            d_fitness = pc_evaluator->dEvaluate(vec_genotype);
        }
        return d_fitness;
    }else {
        return d_Wrong_value;
    }
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
    b_initilised = c_other.b_initilised;
}

void CInvidual::vCopyMove(CInvidual &&c_other) {
    pc_evaluator = c_other.pc_evaluator;
    pc_random_generator = c_other.pc_random_generator;
    vec_genotype = move(c_other.vec_genotype);
    d_fitness = c_other.d_fitness;
    b_initilised = c_other.b_initilised;

    c_other.d_fitness = c_other.d_Wrong_value;
    c_other.pc_evaluator = nullptr;
    c_other.pc_random_generator = nullptr;
    c_other.b_initilised = false;
}


