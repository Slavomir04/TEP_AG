//
// Created by Slawomir on 11.01.2025.
//

#include <gtest/gtest.h>

#include "GeneticAlgorithm/CInvidual.h"
#include "GeneticAlgorithm/Evaluator.h"


using namespace std;
TEST(EvaluatorTest, init) {
    const int i_count_points = 100;
    const int i_groups = 50;
    vector<Point> vec_points;
    vector<int> vec_genotype;
    int result_1000 = 2236;
    int i_temp = 1;
    for (int i = 0; i < i_count_points; i++) {
        vec_points.push_back(Point({(double)i,(double)i*2}));
        vec_genotype.push_back(i_temp);
        i_temp+=(i)%2;
    }

    Evaluator eval(vec_points,i_groups);

    EXPECT_EQ(i_groups,eval.iGetNumGroups());
    EXPECT_EQ(eval.iGetPointsCount(),i_count_points);
    EXPECT_EQ(eval.dEvaluate(vec_genotype)>0,true);

}







