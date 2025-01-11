//
// Created by Slawomir on 11.01.2025.
//

#include <gtest/gtest.h>
#define private public
#include "GroupingChallenge/Optimizer.h"
#undef private

#include "GroupingChallenge/GaussianGroupingEvaluatorFactory.h"
#include "GroupingChallenge/GroupingEvaluator.h"


using namespace NGroupingChallenge;
TEST(OptimizerTest,distributionBoundsTest) {
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

    COptimizer c_optimizer(*pc_evaluator);
    c_optimizer.vInitialize();


    EXPECT_EQ(c_optimizer.c_distribution_leftBound_rightBound.min(),pc_evaluator->iGetLowerBound());
    EXPECT_EQ(c_optimizer.c_distribution_leftBound_rightBound.max(),pc_evaluator->iGetUpperBound());

    EXPECT_EQ(c_optimizer.c_distribution_0_1.min(),0);
    EXPECT_EQ(c_optimizer.c_distribution_0_1.max(),1);
    delete pc_evaluator;
}

TEST(OptimizerTest,mutationFunctionsTest) {
    int i_groups = 5;
    int i_points = 5;
    CGaussianGroupingEvaluatorFactory c_evaluator_factory(i_groups, i_points, 5);

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

    COptimizer c_optimizer(*pc_evaluator);
    c_optimizer.vInitialize();


    vector<int> v1 = {1,2,3,4,5};
    vector<int> v2 = {5,4,3,2,1};

    c_optimizer.v_points_group_position[0] = v1;
    c_optimizer.v_points_group_position[1] = v2;

    vector<int> result;
    std::pair<vector<int>&,vector<int>&> pair_(v1,v2);


    result = {1,2,3,2,1};
    pair_ = c_optimizer.pairvCrossTwoGroups(0,1,2);
    EXPECT_EQ(pair_.first,result);

    result = {5,4,3,4,5};
    pair_ = c_optimizer.pairvCrossTwoGroups(0,1,2);
    EXPECT_EQ(pair_.second,result);

    result = {1,4,3,2,1};
    pair_ = c_optimizer.pairvCrossTwoGroups(0,1,1);
    EXPECT_EQ(pair_.first,result);

    result = {5,2,3,4,5};
    pair_ = c_optimizer.pairvCrossTwoGroups(0,1,1);
    EXPECT_EQ(pair_.second,result);


    delete pc_evaluator;
}




