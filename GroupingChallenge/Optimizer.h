#ifndef OPTIMIZER_H
#define OPTIMIZER_H

#include "GroupingEvaluator.h"

#include <iostream>
#include <numeric>
#include <random>
#include <vector>
using namespace std;

namespace NGroupingChallenge
{
	class COptimizer
	{
	public:
		COptimizer(CGroupingEvaluator& cEvaluator);

		void vInitialize();		//nie zmieniaj nazwy
		void vRunIteration();  //nie zmieniaj nazwy

		vector<int>* pvGetCurrentBest() { return &v_current_best; }

		void vShowGroups();
	private:

		CGroupingEvaluator& c_evaluator; //nie zmieniaj

		double d_current_best_fitness;  //nie zmieniaj
		vector<int> v_current_best; //nie zmieniaj
		mt19937 c_random_engine;

		//probabilities
		const float fl_cross_probability;
		const float fl_mut_probability;


		const int i_pop_size;

		vector<vector<int>> v_points_group_position;

		//distributions
		std::uniform_int_distribution<int> c_distribution_0_pointscount;
		std::uniform_int_distribution<int> c_distribution_leftBound_rightBound;
		std::uniform_real_distribution<float> c_distribution_0_1;

		//methods
		void vSetRandomGroupsOfPoints();
		void vCross();
		void vMut();
		void vEvaluate();
		std::pair<vector<int>,vector<int>> pairvCrossTwoGroups(int i_index_1,int i_index_2,int i_position);




	};
}

#endif