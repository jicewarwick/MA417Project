#ifndef CALIBRATION_H_AASIHOBC
#define CALIBRATION_H_AASIHOBC

#include "HestonModel.h"
#include "MonteCarloSimulation.h"
#include <gsl/gsl_multifit_nlin.h>

class HestonCalibration {
public:
	HestonCalibration (MonteCarloSimulation* );
	virtual ~HestonCalibration ();
	int calibrate();
	HestonModel* ReturnCalibrated();

	struct data{
		size_t n;
		double* y;
		double* sigma;
	};

private:
	int N_smples_;
	double* call_prices_;
	double* strike_prices_;
	int f(const gsl_vector* x, void *data, gsl_vector* f);
};

#endif /* end of include guard: CALIBRATION_H_AASIHOBC */

