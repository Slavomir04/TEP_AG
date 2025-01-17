//
// Created by Slawomir on 13.01.2025.
//

#include "CGeneticAlgorithm.h"




CGeneticAlgorithm::CGeneticAlgorithm(NGroupingChallenge::CGroupingEvaluator& evaluator) : evaluator(evaluator) {
        c_distribution_invidual = uniform_int_distribution<int>(0,i_population-1);
        c_distribution_0_1 = uniform_real_distribution<double>(0,1);
        vReset();
}

void CGeneticAlgorithm::vInitilized() {
    vReset();
    for (int i=0; i<i_population; i++) {
        vec_population.emplace_back(&evaluator,&c_random_generator);
    }
}

void CGeneticAlgorithm::vRun() {
        std::chrono::high_resolution_clock::time_point time_start = timeGetCurrentTime();
        bool b_loop = true;

        while (b_loop) {
            vMutate();
            vCross();
            vEvaluate();
            std::chrono::duration<double> time_elapsed = timeGetCurrentTime() - time_start;
            if (time_elapsed.count() > d_run_time_sec) {
                b_loop = false;
            }
        }

}


vector<int> CGeneticAlgorithm::vecGetBestSolution() {
    return c_best_individual.vecGetGenotype();
}

double CGeneticAlgorithm::dGestBestFitness() {
    return d_best_fitness;
}

void CGeneticAlgorithm::vSetMutationProbability(double d_new_probability) {
    if(d_new_probability > 0) {
        this->d_mut_probability = d_new_probability;
    }
}

void CGeneticAlgorithm::vSetCrossoverProbability(double d_new_probability) {
    if(d_new_probability > 0) {
        this->d_cross_probability = d_new_probability;
    }
}

void CGeneticAlgorithm::vSetRunTime(double d_time_seconds) {
    if(d_time_seconds > 0) {
        this->d_run_time_sec = d_time_seconds;
    }
}

void CGeneticAlgorithm::vSetEvenPopulationSize(int i_new_size) {
    if(i_new_size>=2 && i_new_size%2==0) {
        this->i_population = i_new_size;
    }
}


void CGeneticAlgorithm::vEvaluate() {
    for (int i=0; i<i_population; i++) {
        vCheckBest(vec_population[i]);
    }
}

void CGeneticAlgorithm::vCross() {
    vector<CInvidual> vec_next_gen(i_population);
    for (int i=0; i<i_population; i+=2) {
        int i_parent_a = iGetParents(c_random_generator.iGetRandomNumber(c_distribution_invidual),
            c_random_generator.iGetRandomNumber(c_distribution_invidual));
        int i_parent_b = iGetParents(c_random_generator.iGetRandomNumber(c_distribution_invidual),
            c_random_generator.iGetRandomNumber(c_distribution_invidual));

        pair<CInvidual,CInvidual> paircNewParentsCross = vec_population[i_parent_a].paircCrossover(d_cross_probability,vec_population[i_parent_b]);
        vec_next_gen[i] = move(paircNewParentsCross.first);
        vec_next_gen[i+1] = move(paircNewParentsCross.second);
    }
    vec_population = move(vec_next_gen);
}

void CGeneticAlgorithm::vMutate() {
    for (int i=0; i<i_population; i++)vec_population[i].vMutation(d_mut_probability);
}

void CGeneticAlgorithm::vCheckBest(CInvidual &c_invidual) {
    double d_fitness = c_invidual.dEvaluate();
    if(d_fitness < d_best_fitness) {
        d_best_fitness = d_fitness;
        c_best_individual = c_invidual;
    }
}



void CGeneticAlgorithm::vReset() {
    vec_population = vector<CInvidual>();
    d_best_fitness = DBL_MAX;
    vector<int> vec_temp = {i_wrong_value};
    c_best_individual = CInvidual(&evaluator,&c_random_generator,vec_temp);

}

int CGeneticAlgorithm::iGetParents(int i_candidate_a, int i_candidate_b) {
    return vec_population[i_candidate_a].dEvaluate()<vec_population[i_candidate_b].dEvaluate() ?
        i_candidate_a : i_candidate_b;
}

std::chrono::high_resolution_clock::time_point CGeneticAlgorithm::timeGetCurrentTime() {
    return std::chrono::high_resolution_clock::now();
}

