//
// Created by Slawomir on 13.01.2025.
//

#include "RandomGenerator.h"

RandomGenerator::RandomGenerator(){
    std::random_device c_rd;
    c_random_engine = std::mt19937(c_rd());
}

double RandomGenerator::dGetRandomNumber(double d_left, double d_right){
    std::uniform_real_distribution<double> c_distribution(d_left, d_right);
    return c_distribution(c_random_engine);
}

int RandomGenerator::iGetRandomNumber(int i_left, int i_right){
    std::uniform_int_distribution<int> c_distribution(i_left, i_right);
    return c_distribution(c_random_engine);
}

double RandomGenerator::dGetRandomNumber(std::uniform_real_distribution<double> &uniform) {
    return uniform(c_random_engine);
}

int RandomGenerator::iGetRandomNumber(std::uniform_int_distribution<int> &uniform) {
    return uniform(c_random_engine);
}
