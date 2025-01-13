#include <iostream>
#include <random>

#include "GeneticAlgorithm/CGeneticAlgorithm.h"
#include "GeneticAlgorithm/CInvidual.h"
#include "GeneticAlgorithm/Evaluator.h"
#include "GeneticAlgorithm/Point.h"
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


    //hyper Cinvidual test


    vector<Point> vec;
    for (int i = 0; i < 5; i++)vec.push_back(Point({(double)i}));
    Evaluator evaluator(vec,5);
    RandomGenerator generator;
    //
    vector<int> v1 = {1,2,3,4,5};
    vector<int> v2 = {5,4,3,2,1};
    CInvidual inv1(&evaluator,&generator,v1);
    CInvidual inv2(&evaluator,&generator,v2);

    pair<CInvidual,CInvidual> pair= inv1.paircCrossover(move(inv2));

    vShow(pair.first.vecGetGenotype());
    vShow(pair.second.vecGetGenotype());





    return 0;
}

