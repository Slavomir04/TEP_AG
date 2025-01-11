#include "Optimizer.h"

#include <float.h>

using namespace NGroupingChallenge;

COptimizer::COptimizer(CGroupingEvaluator& cEvaluator)
	: c_evaluator(cEvaluator),fl_cross_probability(0.6),fl_mut_probability(0.1),i_pop_size(8)
{
	random_device c_seed_generator;
	c_random_engine.seed(c_seed_generator());


}

void COptimizer::vInitialize()
{
	numeric_limits<double> c_double_limits;
	d_current_best_fitness = c_double_limits.max();

	v_current_best.clear();
	v_current_best.resize(c_evaluator.iGetNumberOfPoints());

	c_distribution_0_pointscount = std::uniform_int_distribution<int>(0,c_evaluator.iGetNumberOfPoints()-1);
	c_distribution_leftBound_rightBound = std::uniform_int_distribution<int>(c_evaluator.iGetLowerBound(), c_evaluator.iGetUpperBound());
	c_distribution_0_1 = std::uniform_real_distribution<float>(0,1);

	vSetRandomGroupsOfPoints();
	vEvaluate();
}

void COptimizer::vRunIteration()
{
	//crossing
	vCross();

	//mutation
	vMut();

	//evaluation
	vEvaluate();


	printf("best fit is %.2f\n", d_current_best_fitness);
}

void COptimizer::vShowGroups() {
	cout << "-----\n";
	for (int i=0; i<i_pop_size; i++) {
		for (int j=0; j<v_points_group_position[i].size(); j++) {
			cout << v_points_group_position[i][j] << " ";
		}
		cout << endl;
	}
}



void COptimizer::vSetRandomGroupsOfPoints() {
	v_points_group_position = std::vector<vector<int>>(i_pop_size);

	int i_count_points = c_evaluator.iGetNumberOfPoints();

	for (int i=0; i < i_pop_size; i++) {
		v_points_group_position[i] = std::vector<int>(i_count_points);
		for (int j=0; j < i_count_points; j++) {
			v_points_group_position[i][j] = c_distribution_leftBound_rightBound(c_random_engine);
		}
	}

}

void COptimizer::vCross() {
	vector<vector<int>> v_next_gen(i_pop_size);
	for (int i=0; i<i_pop_size; i+=2) {

		int i_temp_10 = c_distribution_leftBound_rightBound(c_random_engine);
		int i_temp_11 = c_distribution_leftBound_rightBound(c_random_engine);

		int i_temp_20 = c_distribution_leftBound_rightBound(c_random_engine);
		int i_temp_21 = c_distribution_leftBound_rightBound(c_random_engine);

		int i_index_left = ( c_evaluator.dEvaluate(v_points_group_position[i_temp_10]) < c_evaluator.dEvaluate(v_points_group_position[i_temp_11])) ? i_temp_10 : i_temp_11;
		int i_index_right = ( c_evaluator.dEvaluate(v_points_group_position[i_temp_20]) < c_evaluator.dEvaluate(v_points_group_position[i_temp_21])) ? i_temp_20 : i_temp_21;

		int i_cut_position = c_distribution_leftBound_rightBound(c_random_engine) - c_evaluator.iGetLowerBound();

		if (c_distribution_0_1(c_random_engine)<fl_cross_probability) {
			std::pair<vector<int>,vector<int>> pairv_current_cross= std::move(pairvCrossTwoGroups(i_index_left, i_index_right,i_cut_position));
			v_next_gen[i] = std::move(pairv_current_cross.first);
			v_next_gen[i+1] = std::move(pairv_current_cross.second);
		}else {
			v_next_gen[i] = v_points_group_position[i_index_left];
			v_next_gen[i+1] = v_points_group_position[i_index_right];
		}
	}

	v_points_group_position = std::move(v_next_gen);
}

void COptimizer::vMut() {
	for (int i=0; i < v_points_group_position.size(); i++) {
		for (int j=0; j < v_points_group_position[i].size(); j++) {
			if (c_distribution_0_1(c_random_engine)<fl_mut_probability) { //mutacja
				v_points_group_position[i][j] = c_distribution_leftBound_rightBound(c_random_engine);
			}
		}
	}
}

void COptimizer::vEvaluate() {
	for (int i=0; i<v_points_group_position.size(); i++) {
		double d_temp = c_evaluator.dEvaluate(v_points_group_position[i]);
		if (d_temp < d_current_best_fitness) {
			d_current_best_fitness = d_temp;
			v_current_best = v_points_group_position[i];
		}
	}


}

std::pair<vector<int> , vector<int> > COptimizer::pairvCrossTwoGroups(int i_index_1, int i_index_2, int i_position) {
	int i_count_points = c_evaluator.iGetNumberOfPoints();
	vector<int> v_left(i_count_points);
	vector<int> v_right(i_count_points);

	int index=0;
	while (index<i_position) {
		v_left[index] = v_points_group_position[i_index_1][index];
		v_right[index] = v_points_group_position[i_index_2][index];
		index++;
	}
	while (index<=i_count_points) {
		v_left[index] = v_points_group_position[i_index_2][index];
		v_right[index] = v_points_group_position[i_index_1][index];
		index++;
	}

	return std::pair<vector<int>, vector<int>>(std::move(v_left), std::move(v_right));
}









