#include <iostream>
#include "GeneticAlgorithm/CGeneticAlgorithm.h"
#include "GeneticAlgorithm/CInvidual.h"
#include "GeneticAlgorithm/Evaluator.h"
#include "GeneticAlgorithm/Point.h"
#include <chrono>


#include "GroupingChallenge/Point.h"
#include "GroupingChallenge/Point.h"
using namespace std;

void vShow(vector<Point> vec) {
    cout<<"{";
    for (auto&e : vec) {
        cout<<"{";
        for (auto &d : e.vecGetDimension())cout<<d<<",";
        cout<<"} ";
    }
    cout<<"}"<<endl;
}
void vShow(vector<int> vec) {
    cout<<"{";
    for (auto&e : vec)cout<<e<<",";
    cout<<"}"<<endl;
}


void vIterate(vector<CInvidual>& population,RandomGenerator& random_generator){
    for (int i=0; i<population.size(); i++) {
        population[i].vMutation(0.1);
    }
    vector<CInvidual> vec_next_gen(population.size());
    for (int i=0; i<population.size(); i+=2) {
        int i_inv1 = random_generator.iGetRandomNumber(0,population.size()-1);
        int i_inv2 = random_generator.iGetRandomNumber(0,population.size()-1);
        int i_inv3 = random_generator.iGetRandomNumber(0,population.size()-1);
        int i_inv4 = random_generator.iGetRandomNumber(0,population.size()-1);

        int i_win1 = population[i_inv1].dEvaluate()<population[i_inv2].dEvaluate() ? i_inv1 : i_inv2;
        int i_win2 =population[i_inv3].dEvaluate()<population[i_inv4].dEvaluate() ? i_inv3 : i_inv4;

        pair<CInvidual,CInvidual> pairc_winner_cross = {population[i_win1].paircCrossover(population[i_win2])};
        vec_next_gen[i] = move(pairc_winner_cross.first);
        vec_next_gen[i+1] = move(pairc_winner_cross.second);
    }
    population = move(vec_next_gen);
}



int main() {
    int points = 100;
    int range = 10;
    int groups = 15;
    int pop = 50;
    mt19937_64 rng;
    uniform_real_distribution<double> dist_100(-range, range);
    vector<Point> vec;
    for (int i = 0; i < points; i++)vec.push_back(Point({dist_100(rng),dist_100(rng),dist_100(rng)}));
    Evaluator evaluator(vec,groups);
    RandomGenerator generator;

    CGeneticAlgorithm genetic_algorithm(&evaluator);
   genetic_algorithm.run();


    return 0;
}

