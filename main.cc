/* Projcet AIMS
 * 1. Simulate Heston Model
 * 2. Compute European Call option under Heston Model
 * 3. Calibration using GNU Scientific Library to minimise norm 2 distance
 * 4. Compute barrier option and Asian option prices under Heston Model
 */

#include <iostream>
#include <functional>
#include <algorithm>
#include <gsl/gsl_multifit_nlin.h>
#include "NormalRandomNumberGenerator.h"
#include "HestonModel.h"
#include "dataExport.h"
#include "Options.h"
#include "MonteCarloSimulation.h"

#include "f.cc"

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
/*	
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

	Q1->~HestonModel();
*/
	// calibration
	const int kNumK = 7;
	const int kNumVar = 5;
	T = 1;
	S0 = 14.97;
	r = 0.0;
	double K[kNumK] = 				{10.0,	12.5,	15.0,	17.5,	20.0,	22.5,	25.0};
	double market_price[kNumK] = 	{5.43,	3.35,	1.85,	0.9,	0.4,	0.18,	0.09};

	//x_init is the initial guess.
	double x_init[kNumVar] = {0.1, 0.1, 0.1, 0.1, 0.1};
	gsl_vector_view x = gsl_vector_view_array(x_init, kNumVar);
	struct data d = {kNumVar, K, market_price, norm};

	gsl_multifit_function_fdf f;
	f.f = &func;
	f.df = NULL;
	f.fdf = NULL;
	f.n = kNumK;
	f.p = kNumVar;
	f.params = &d;

	const gsl_multifit_fdfsolver_type *solver_type = gsl_multifit_fdfsolver_lmder;
	gsl_multifit_fdfsolver* s =  gsl_multifit_fdfsolver_alloc(solver_type, kNumK, kNumVar);
	gsl_multifit_fdfsolver_set(s, &f, &x.vector);

	int status;
	int iter = 0;
	do {
		++iter;
		status = gsl_multifit_fdfsolver_iterate(s);

		std::cout << "status = " << gsl_strerror(status) << std::endl;

		if (status) {
			break;
		}
		status = gsl_multifit_test_delta(s->dx, s->x, 1e-4, 1e-4);

	} while(status == GSL_CONTINUE && iter < 500);

	std::cout << "iter: " << iter << std::endl;
	std::cout << "alpha	= " << gsl_vector_get(s->x, 0) << std::endl;
	std::cout << "beta	= " << gsl_vector_get(s->x, 1) << std::endl;
	std::cout << "gamma	= " << gsl_vector_get(s->x, 2) << std::endl;
	std::cout << "rho	= " << gsl_vector_get(s->x, 3) << std::endl;
	std::cout << "v_0	= " << gsl_vector_get(s->x, 4) << std::endl;

	norm->~NormalRandomNumberGenerator();
	return 0;
}
