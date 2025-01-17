//
// Created by Slawomir on 13.01.2025.
//
#include "CInvidual.h"
#include <iostream>
#include <stdexcept>


CInvidual::CInvidual(NGroupingChallenge::CGroupingEvaluator* pc_evaluator,RandomGenerator* pc_random_generator) {
    vFirstInit(pc_evaluator, pc_random_generator);
    if (b_initilised) {
        vRandomInit();
    }
}

CInvidual::CInvidual(NGroupingChallenge::CGroupingEvaluator* pc_evaluator,RandomGenerator* pc_random_generator, vector<int> &vec_genotype) {
    vFirstInit(pc_evaluator, pc_random_generator);
    this->vec_genotype = move(vec_genotype);
}

CInvidual::CInvidual(CInvidual &&c_other) {
    vFirstInit(nullptr, nullptr);
    vCopyMove(move(c_other));
}

CInvidual::CInvidual(const CInvidual &c_other) {
    vFirstInit(nullptr, nullptr);
    vCopy(c_other);
}


CInvidual& CInvidual::operator=(const CInvidual&  c_other){
    if(this != &c_other) {
        vFirstInit(nullptr, nullptr);
        vCopy(c_other);
    }
    return *this;
}
CInvidual& CInvidual::operator=(CInvidual&& c_other) {
    if(this!= &c_other) {
        vFirstInit(nullptr,nullptr);
        vCopyMove(move(c_other));
    }
    return *this;
}
void CInvidual::vMutation(double d_probability) {
    if (b_initilised) {
        d_fitness = d_Wrong_value;
        uniform_int_distribution<int> c_distribution_point = uniform_int_distribution<int>(pc_evaluator->iGetLowerBound(), pc_evaluator->iGetUpperBound());
        for (int i=0; i<this->vec_genotype.size(); i++) {
            if (pc_random_generator->dGetRandomNumber(c_distribution_0_1)<d_probability) {
                vec_genotype[i] = pc_random_generator->iGetRandomNumber(c_distribution_point);
            }
        }
    }
}

pair<CInvidual, CInvidual> CInvidual::paircCrossover(double d_probability,const CInvidual &c_other) {
    if(pc_random_generator->dGetRandomNumber(c_distribution_0_1) < d_probability) {
        pair<CInvidual, CInvidual> c_result;
        if (this->vec_genotype.size() == c_other.vec_genotype.size() && this->vec_genotype.size() > 1) {
            CInvidual c_new_1(*this);
            CInvidual c_new_2(c_other);

            int index = pc_random_generator->iGetRandomNumber(1, this->vec_genotype.size()-2);
            while (index < this->vec_genotype.size()) {
                c_new_1.vec_genotype[index] = c_other.vec_genotype[index];
                c_new_2.vec_genotype[index] = vec_genotype[index];
                index++;
            }

            c_result = make_pair(c_new_1, c_new_2);
        }else {
            c_result = {*this, c_other};
        }
        return c_result;
    }return{*this, c_other};
}


double CInvidual::dEvaluate() {
    if (b_initilised) {
        if (d_fitness == d_Wrong_value) {
            //const vector<int> &v = this->vec_genotype;
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
    vFirstInit(nullptr,nullptr);
}

void CInvidual::vFirstInit( NGroupingChallenge::CGroupingEvaluator* pc_evaluator,RandomGenerator* pc_random_generator) {
    c_distribution_0_1 = uniform_real_distribution<double>(0,1);
    d_fitness = d_Wrong_value;
    this->pc_evaluator = pc_evaluator;
    this->pc_random_generator = pc_random_generator;
    b_initilised = pc_evaluator != nullptr && pc_random_generator != nullptr;
    vec_genotype = {(int)d_Wrong_value};
}

void CInvidual::vRandomInit() {
    uniform_int_distribution<int> c_distribution_point = uniform_int_distribution<int>(pc_evaluator->iGetLowerBound(),pc_evaluator->iGetUpperBound());
    vec_genotype = vector<int>(pc_evaluator->iGetNumberOfPoints());
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
    c_other.vec_genotype = {(int)d_Wrong_value};
}


