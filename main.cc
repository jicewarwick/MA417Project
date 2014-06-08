/* Projcet AIMS
 * 1. Simulate Heston Model
 * 2. Compute European Call option under Heston Model
 * 3. Calibration using GNU Scientific Library to minimise norm 2 distance
 * 4. Compute barrier option and Asian option prices under Heston Model
 */

#include <iostream>
#include <functional>
#include <algorithm>
#include "NormalRandomNumberGenerator.h"
#include "Model.h"
#include "HestonModel.h"
#include "dataExport.h"
#include "Options.h"
#include "MonteCarloSimulation.h"

int main(int argc, char *argv[]) {
	//Simulate Heston Model
	
	//parameter initilisation:
	int N_int = 100;
	int N_sim = 10000;
	double S0 = 10;
	double r = 0;
	double v0 = 0.04;
	double alpha = 2;
	double beta = 0.04;
	double gamma = 0.2;
	double rho = -0.2;
	double T = 1;

	NormalRandomNumberGenerator* norm = new NormalRandomNumberGenerator();
	HestonModel* Q1 = new HestonModel(alpha, beta, gamma, rho, v0, r, S0, T, N_int, norm);

	std::vector<double> call_K;
	call_K.push_back(10.0);
	call_K.push_back(3.0);
	
	MonteCarloSimulation sim_call_price(Q1, call_K, EuropeanCallVal, N_sim);
	sim_call_price.exec();
	double call_price = sim_call_price.get_results();
	std::cout << "European Call option price: " << call_price << std::endl;

	MonteCarloSimulation sim_barrier_call_price(Q1, call_K, DownAndOutCallVal, N_sim);
	sim_barrier_call_price.exec();
	double barrier_call_price = sim_barrier_call_price.get_results();
	std::cout << "Down-and-Out Call option price: " << barrier_call_price << std::endl;

	norm->~NormalRandomNumberGenerator();
	Q1->~HestonModel();
	return 0;
}
