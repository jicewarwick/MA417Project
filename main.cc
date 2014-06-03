/* Projcet AIMS
 * 1. Simulate Heston Model
 * 2. Compute European Call option under Heston Model
 * 3. Calibration using GNU Scientific Library to minimise norm 2 distance
 * 4. Compute barrier option and Asian option prices under Heston Model
 */

#include <iostream>
#include "NormalRandomNumberGenerator.h"
#include "HestonModel.h"
#include "dataExport.h"
#include "Options.h"

double EuropeanCallWithK(HestonModel& model, double K);

int main(int argc, char *argv[]) {
	//Simulate Heston Model
	
	//parameter initilisation:
	int N_int = 1000;
	int N_sim = 100;
	double S0 = 10;
	double r = 0;
	double v0 = 0.04;
	double alpha = 2;
	double beta = 0.04;
	double gamma = 0.2;
	double rho = -0.2;
	double T = 1;
	int dim = T*N_int+1;

	NormalRandomNumberGenerator* norm = new NormalRandomNumberGenerator();
	HestonModel Q1(alpha, beta, gamma, rho, v0, r, S0, T, N_int, norm);
	
	return 0;
}

double EuropeanCallWithK(HestonModel& model, double K){
	double ST = model.get_ST();
	return (EuropeanCallVal(ST, K));

}
