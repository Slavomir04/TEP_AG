#include <iostream>
#include "GeneticAlgorithm/CGeneticAlgorithm.h"
#include "GeneticAlgorithm/CInvidual.h"
#include "GeneticAlgorithm/Evaluator.h"
#include "GeneticAlgorithm/Point.h"
#include "GeneticAlgorithm/CGeneticAlgorithm.h"
#include <chrono>

#include "GeneticAlgorithm/MyEvaluatorFactory.h"
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







int main() {

    vector<Point> points = {
        {{2,-3}},
        {{3,-2}},
        {{1,5}},
        {{3,4}},
        {{-5,4}},
        {{-7,1}},
        {{0,0}},
    };
    Evaluator evaluator(points,3);
    CGeneticAlgorithm algorithm(&evaluator);
    algorithm.run();
    vector<int> result = algorithm.cGetBestIndividual().vecGetGenotype();
    vShow(result);

    /*
    int i_points = 100;
    int i_dims = 3;
    int i_range = 100;
    int i_groups = 5;
    MyEvaluatorFactory factory(100,3,100,5);
    Evaluator* pc_evaluator = factory.createEvaluator();
    CGeneticAlgorithm c_genetic_algorithm(pc_evaluator);
    c_genetic_algorithm.run();
    vShow(c_genetic_algorithm.cGetBestIndividual().vecGetGenotype());
    delete pc_evaluator;
    */
    return 0;
}

