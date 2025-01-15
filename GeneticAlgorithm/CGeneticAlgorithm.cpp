//
// Created by Slawomir on 13.01.2025.
//

#include "CGeneticAlgorithm.h"

#include <chrono>


CGeneticAlgorithm::CGeneticAlgorithm(Evaluator *evaluator) {
    b_initalised = evaluator!=nullptr;
    if (b_initalised) {


        this->evaluator = evaluator;
        i_population = evaluator->iGetPointsCount()/2;
        if (i_population==0)i_population =2;
        else if (i_population%2!=0)i_population +=1;

        c_distribution_point = uniform_int_distribution<int>(0,i_population-1);
        c_distribution_0_1 = uniform_real_distribution<double>(0,1);

        for (int i=0; i<i_population; i++) {
            vec_population.emplace_back(evaluator,&c_random_generator);
        }

        d_best_fitness = DBL_MAX;
        vEvaluate();
    }
}

void CGeneticAlgorithm::run() {
    if (b_initalised) {
        std::chrono::high_resolution_clock::time_point time_start = std::chrono::high_resolution_clock::now();
        bool b_loop = true;
        cout<<"start best fitness: "<<d_best_fitness<<endl;
        while (b_loop) {
            vMutate();
            vCross();
            vEvaluate();
            std::chrono::duration<double> time_elapsed = std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - time_start);
            double d_counted = time_elapsed.count();
            if (d_counted > d_run_time_sec) {
                b_loop = false;
            }
            cout<<"current fitness: "<<d_best_fitness<<endl;
        }
        cout<<"best fitness: "<<d_best_fitness<<endl;
    }
}

CInvidual CGeneticAlgorithm::cGetBestIndividual() {
    return c_best_individual;
}



void CGeneticAlgorithm::vEvaluate() {
    for (int i=0; i<i_population; i++) {
        double d_current_fitness = vec_population[i].dEvaluate();
        if (d_current_fitness < d_best_fitness) {
            d_best_fitness = d_current_fitness;
            c_best_individual = vec_population[i];
        }
    }
}

void CGeneticAlgorithm::vCross() {
    for (int i=0; i<i_population; i++) {
        vec_population[i].vMutation(0.1);
    }
    vector<CInvidual> vec_next_gen(i_population);
    for (int i=0; i<i_population; i+=2) {
        if (c_random_generator.dGetRandomNumber(c_distribution_0_1) < d_cross_probability) {
            int i_inv1 = c_random_generator.iGetRandomNumber(c_distribution_point);
            int i_inv2 = c_random_generator.iGetRandomNumber(c_distribution_point);
            int i_inv3 = c_random_generator.iGetRandomNumber(c_distribution_point);
            int i_inv4 = c_random_generator.iGetRandomNumber(c_distribution_point);

            int i_win1 = vec_population[i_inv1].dEvaluate()<vec_population[i_inv2].dEvaluate() ? i_inv1 : i_inv2;
            int i_win2 =vec_population[i_inv3].dEvaluate()<vec_population[i_inv4].dEvaluate() ? i_inv3 : i_inv4;

            pair<CInvidual,CInvidual> pairc_winner_cross = {vec_population[i_win1].paircCrossover(vec_population[i_win2])};
            vec_next_gen[i] = move(pairc_winner_cross.first);
            vec_next_gen[i+1] = move(pairc_winner_cross.second);
        }else {
            vec_next_gen[i] = vec_population[i];
            vec_next_gen[i+1] = vec_population[i+1];
        }
    }
    vec_population = move(vec_next_gen);
}

void CGeneticAlgorithm::vMutate() {
    for (int i=0; i<i_population; i++)vec_population[i].vMutation(d_mut_probability);
}
