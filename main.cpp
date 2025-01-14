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

vector<int> vecFinSolution(vector<Point> points,int i_groups) {
    Evaluator evaluator(points,i_groups);
    CGeneticAlgorithm algorithm(&evaluator);
    algorithm.run();
    return algorithm.cGetBestIndividual().vecGetGenotype();
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

    vector<int> result = vecFinSolution(points,3);
    vShow(result);


    return 0;
}

