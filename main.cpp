#include <iostream>
#include "GeneticAlgorithm/CGeneticAlgorithm.h"
#include "GeneticAlgorithm/CInvidual.h"
#include "GeneticAlgorithm/Evaluator.h"
#include "GeneticAlgorithm/Point.h"
#include <chrono>


#include "GroupingChallenge/Point.h"
#include "GroupingChallenge/Point.h"
#include "Visual/Visual.h"
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

vector<pair<double,double>> vecConvertToPairPoint(vector<Point>& vec) {
    vector<pair<double,double>> vec_result;
    for (auto &p : vec) {
        if (p.vecGetDimension().size()==2) {
            vec_result.emplace_back(p.vecGetDimension()[0],p.vecGetDimension()[1]);
        }
    }
    return vec_result;
}

void vMakeVisual(Evaluator* evaluator,vector<int>& vec_genotype,vector<sf::Color> vec_colors) {
    cout<<"Running visualizer...";
    Visual visual(1000,1000,"visual",15,15);
    visual.vSetColors(vec_colors);
    vector<Point> points = move(evaluator->vecGetPoints());
    visual.vSetPoints(vecConvertToPairPoint(points));
    visual.vPaint(vec_genotype,evaluator->iGetLowBound());
    visual.run();
}
void vMakeVisual(Evaluator* evaluator,vector<int>& vec_genotype) {
    vector<sf::Color> colors;
    for (int i=0; i<=evaluator->iGetNumGroups(); i++) {
        int modifier = 255/evaluator->iGetNumGroups();
        cout<<"current color: "<<i*modifier<<endl;
        colors.emplace_back(i*modifier,i*modifier,i*modifier);
    }
    vMakeVisual(evaluator,vec_genotype,colors);
}
int main() {

    vector<Point> points = {
        {{2,-3}},
        {{3,-2}},
        {{1,5}},
        {{3,4}},
        {{-5,4}},
        {{-7,1}},
    };
    int i_groups = 3;
    Evaluator evaluator(points,i_groups);
    CGeneticAlgorithm algorithm(&evaluator);
    algorithm.run();
    vShow(algorithm.cGetBestIndividual().vecGetGenotype());
    vMakeVisual(&evaluator,algorithm.cGetBestIndividual().vecGetGenotype(),{sf::Color::Yellow,sf::Color::Green,sf::Color::Red});



    return 0;
}

