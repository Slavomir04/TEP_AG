//
// Created by Slawomir on 13.01.2025.
//

#ifndef RANDOMGENERATOR_H
#define RANDOMGENERATOR_H
#include <random>


class RandomGenerator {
public:
  RandomGenerator();
  double dGetRandomNumber(double d_left,double d_right);
  int iGetRandomNumber(int i_left,int i_right);
  double dGetRandomNumber(std::uniform_real_distribution<double>& uniform);
  int iGetRandomNumber(std::uniform_int_distribution<int>& uniform);
private:
  std::random_device c_rd;
  std::mt19937 c_random_engine;
};



#endif //RANDOMGENERATOR_H
