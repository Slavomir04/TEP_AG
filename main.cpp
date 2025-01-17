#include <iostream>
#include <vector>
#include "GeneticAlgorithm/CGeneticAlgorithm.h"
#include "GroupingChallenge/GaussianGroupingEvaluatorFactory.h"

using namespace NGroupingChallenge;
void vShow(std::vector<int> vec) {
    std::cout<<"{";
    for (auto&e : vec)std::cout<<e<<",";
    std::cout<<"}"<<std::endl;
}

CPoint generatePoint(double x,double y) {
    CPoint p;
    p.vAddCoordinate(x);
    p.vAddCoordinate(y);
    return p;
}

int main() {
    /*
    std::vector<CPoint> points;
    points.push_back(generatePoint(3,5));
    points.push_back(generatePoint(4,4));
    points.push_back(generatePoint(-20,7));
    points.push_back(generatePoint(-7,5));
    points.push_back(generatePoint(0,0));
    CGroupingEvaluator evaluator(3,points);
    CGeneticAlgorithm algorithm(evaluator);
    algorithm.vSetCrossoverProbability(0.6);
    algorithm.vSetMutationProbability(0.2);
    algorithm.vSetEvenPopulationSize(12);
    algorithm.vSetRunTime(15);
    algorithm.vInitilized();
    algorithm.vRun();
    vShow(algorithm.vecGetBestSolution());
    cout<<"win:"<<algorithm.dGestBestFitness();
    */
    CGaussianGroupingEvaluatorFactory c_evaluator_factory(5, 100, 5);

    c_evaluator_factory
        .cAddDimension(-100, 100, 1.0, 1.0)
        .cAddDimension(-100, 100, 1.0, 1.0)
        .cAddDimension(-100, 100, 1.0, 1.0)
        .cAddDimension(-100, 100, 1.0, 1.0)
        .cAddDimension(-100, 100, 1.0, 1.0)
        .cAddDimension(-100, 100, 1.0, 1.0)
        .cAddDimension(-100, 100, 1.0, 1.0)
        .cAddDimension(-100, 100, 1.0, 1.0)
        .cAddDimension(-100, 100, 1.0, 1.0)
        .cAddDimension(-100, 100, 1.0, 1.0);

    CGroupingEvaluator* pc_evaluator = c_evaluator_factory.pcCreateEvaluator(0);
    CGeneticAlgorithm algorithm(*pc_evaluator);
    algorithm.vSetCrossoverProbability(0.6);
    algorithm.vSetMutationProbability(0.2);
    algorithm.vSetEvenPopulationSize(900);
    algorithm.vSetRunTime(5);
    algorithm.vInitilized();
    algorithm.vRun();
    cout<<algorithm.dGestBestFitness()<<endl;
    delete pc_evaluator;

    return 0;
}

