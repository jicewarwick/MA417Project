#include <vector>
#include <gsl/gsl_vector.h>
#include "NormalRandomNumberGenerator.h"
#include "HestonModel.h"
#include "MonteCarloSimulation.h"
#include "Options.h"

struct data {
	size_t n;
	double* k;
	double* y;
	NormalRandomNumberGenerator* norm;
};


	//input:
	//	data includes the actural val and number of observations
	//	f is the output vector that gives the difference between the
	//	fitting line and the actural val
int func(const gsl_vector* x, void* data, gsl_vector* f){
	size_t n = ((struct data*)data)->n;
	double* k = ((struct data*)data)->k;
	double* y = ((struct data*)data)->y;
	NormalRandomNumberGenerator* norm = ((struct data*)data)->norm;

	// the variables that we want to evaluate
	double alpha = gsl_vector_get(x, 0);
	double beta = gsl_vector_get(x, 1);
	double gamma = gsl_vector_get(x, 2);
	double rho = gsl_vector_get(x, 3);
	double v_0 = gsl_vector_get(x, 4);

	// constants for the calibration
	double r = 0.0;
	double S0 = 14.97;
	double T = 1.0;
	int N_int = 100;
	int N_sim = 1000;

	for (size_t i = 0; i < n; ++i) {
		std::vector<double> strike;
		strike.push_back(k[i]);

		HestonModel* Q1 = new HestonModel(alpha, beta, gamma, rho, v_0, r, S0, T, N_int, norm);
		MonteCarloSimulation sim_call_price(Q1, strike, EuropeanCallVal, N_sim);
		sim_call_price.exec();
		double call_price = sim_call_price.get_results();
	
		Q1->~HestonModel();
		gsl_vector_set(f, i, call_price - y[i]);
	}
	return GSL_SUCCESS;
}
