//
// Created by Slawomir on 11.01.2025.
//

#include <gtest/gtest.h>
#include "GroupingChallenge/GroupingEvaluator.h"
#include "GroupingChallenge/Point.h"
#define private public
#include "GeneticAlgorithm/CInvidual.h"
#include "GeneticAlgorithm/CGeneticAlgorithm.h"
#undef private
#include "GeneticAlgorithm/RandomGenerator.h"


NGroupingChallenge::CPoint vCreatePoint(std::vector<double> vec) {
    NGroupingChallenge::CPoint p;
    for(int i=0; i<vec.size(); i++)p.vAddCoordinate(vec[i]);
    return move(p);
}



TEST(CInvidual,initTest) {
    using namespace NGroupingChallenge;
    std::vector<CPoint> points ={
    vCreatePoint({3,5}),
    vCreatePoint({4,3}),
    vCreatePoint({-20,7}),
    vCreatePoint({-7,5}),
    vCreatePoint({0,0})
    };
    int i_groups = 3;
    CGroupingEvaluator evaluator(i_groups,points);
    RandomGenerator random_generator;
    vector<int> vec_genotype = {1,2,3};
    vector<int> vec_genotype_copy = {1,2,3};

    CInvidual invidual1;
    CInvidual invidual2(&evaluator,&random_generator,vec_genotype_copy);

    ASSERT_EQ(invidual1.vec_genotype.size(),1);
    EXPECT_EQ(invidual1.vec_genotype[0],invidual1.d_Wrong_value);
    EXPECT_EQ(invidual1.b_initilised,false);
    EXPECT_EQ(invidual1.pc_evaluator,nullptr);
    EXPECT_EQ(invidual1.pc_random_generator,nullptr);
    EXPECT_EQ(invidual1.dEvaluate(),(double)invidual1.d_Wrong_value);
    EXPECT_EQ(invidual1.dEvaluate(),(double)invidual1.d_Wrong_value);
    EXPECT_EQ(invidual1.c_distribution_0_1.a(),0);
    EXPECT_EQ(invidual1.c_distribution_0_1.b(),1);
    invidual1.vMutation(1);
    EXPECT_EQ(invidual1.vec_genotype[0],invidual1.d_Wrong_value);

    ASSERT_EQ(invidual2.vec_genotype,vec_genotype);
    EXPECT_EQ(invidual2.b_initilised,true);
    EXPECT_EQ(invidual2.dEvaluate(),evaluator.dEvaluate(vec_genotype));
    invidual1 = invidual2;
    ASSERT_EQ(invidual1.vec_genotype,vec_genotype);
    EXPECT_EQ(invidual1.b_initilised,true);
    EXPECT_EQ(invidual1.dEvaluate(),evaluator.dEvaluate(vec_genotype));
    ASSERT_EQ(invidual2.vec_genotype,vec_genotype);
    EXPECT_EQ(invidual2.b_initilised,true);
    EXPECT_EQ(invidual2.dEvaluate(),invidual1.dEvaluate());

    CInvidual invidual3 = move(invidual2);
    ASSERT_EQ(invidual3.vec_genotype,vec_genotype);
    EXPECT_EQ(invidual3.b_initilised,true);
    EXPECT_EQ(invidual3.dEvaluate(),evaluator.dEvaluate(vec_genotype));
    EXPECT_EQ(invidual2.b_initilised,false);
    EXPECT_EQ(invidual2.pc_evaluator,nullptr);
    EXPECT_EQ(invidual2.pc_random_generator,nullptr);
    EXPECT_EQ(invidual2.dEvaluate(),invidual2.d_Wrong_value);
    vector<int> vec_bad = {(int)invidual3.d_Wrong_value};
    EXPECT_EQ(invidual2.vecGetGenotype(),vec_bad);

    pair<CInvidual,CInvidual> pairTest = invidual1.paircCrossover(1,invidual2);
    ASSERT_EQ(pairTest.first.b_initilised,invidual1.b_initilised);
    ASSERT_EQ(pairTest.first.vec_genotype,invidual1.vec_genotype);
    ASSERT_EQ(pairTest.second.b_initilised,invidual2.b_initilised);
    ASSERT_EQ(pairTest.second.vec_genotype,invidual2.vec_genotype);

}
TEST(CGeneticAlgorithm,initTest) {
    using namespace NGroupingChallenge;
    std::vector<CPoint> points ={
        vCreatePoint({3,5}),
        vCreatePoint({4,3}),
        vCreatePoint({-20,7}),
        vCreatePoint({-7,5}),
        vCreatePoint({0,0})
        };
    int i_groups = 3;
    CGroupingEvaluator evaluator(i_groups,points);
    RandomGenerator random_generator;

    int i_pop = 50;
    double d_prob_mut = 0.3;
    double d_prob_cross = 0.6;
    double d_run_time = 5.123;

    CGeneticAlgorithm algorithm(evaluator);
    algorithm.vSetEvenPopulationSize(50);
    algorithm.vSetCrossoverProbability(d_prob_cross);
    algorithm.vSetRunTime(d_run_time);
    algorithm.vSetMutationProbability(d_prob_mut);
    algorithm.vSetEvenPopulationSize(i_pop);
    algorithm.vInitilized();
    EXPECT_EQ(algorithm.d_best_fitness,DBL_MAX);
    EXPECT_EQ(algorithm.d_cross_probability,d_prob_cross);
    EXPECT_EQ(algorithm.d_mut_probability,d_prob_mut);
    EXPECT_EQ(algorithm.vec_population.size(),i_pop);
    EXPECT_EQ(algorithm.d_run_time_sec,d_run_time);
    EXPECT_EQ(algorithm.dGestBestFitness(),DBL_MAX);

    algorithm.vSetEvenPopulationSize(-1);
    algorithm.vInitilized();
    EXPECT_EQ(algorithm.vec_population.size(),i_pop);

    algorithm.vSetEvenPopulationSize(41);
    algorithm.vInitilized();
    EXPECT_EQ(algorithm.vec_population.size(),i_pop);

}








