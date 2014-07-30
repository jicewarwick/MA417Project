#include "HestonCalibration.h"

int HestonCalibration::f(const gsl_vector* x, void *data, gsl_vector* v){
	size_t n = ((struct data*)data)->n;
	double* y = ((struct data*)data)->y;
	double* sigma = ((struct data*)data)->sigma;


}
