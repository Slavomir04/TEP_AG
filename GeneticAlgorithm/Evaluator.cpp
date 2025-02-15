//
// Created by Slawomir on 13.01.2025.
//

#include "Evaluator.h"

#include <stdexcept>

Evaluator::Evaluator(vector<Point> vec_points,int i_groups) :
        vec_points(vec_points),i_groups_count(i_groups){
}

double Evaluator::dEvaluate(vector<int>& vec_genotype) {
        double d_distance_sum = 0;
        double d_distance = 0;

        bool b_failure = false;

        if (vec_genotype.size() != iGetPointsCount()) {
                b_failure = true;
        }

        for (int i = 0; i < vec_genotype.size(); i++) {
                if (vec_genotype[i] <= i_groups_count && vec_genotype[i] >= 1) {
                        for (int j = i+1; j < vec_genotype.size(); j++) {
                                if (vec_genotype[i] == vec_genotype[j]) { //ta sama grupa
                                        d_distance = vec_points[i].dCalculateDistance(vec_points[j]);
                                        if (d_distance>0) {
                                                d_distance_sum += d_distance;
                                        }else {
                                                throw std::invalid_argument("negative distance");
                                                b_failure = true;
                                        }
                                }
                        }
                }else {
                        b_failure = true;
                }
        }

        return b_failure ? d_Wrong_value:d_distance_sum;
}

int Evaluator::iGetPointsCount() {
        return vec_points.size();
}

int Evaluator::iGetLowBound() {
        return 1;
}

int Evaluator::iGetHighBound() {
        return i_groups_count;
}

int Evaluator::iGetNumGroups() {
        return i_groups_count;
}




