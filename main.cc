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

int main(int argc, char *argv[]) {
	//Simulate Heston Model
	
	//parameter initilisation:
	int N_int = 1000;
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
	double* stock_path = Q1.stockPathFactory();

	int N = 10;
	double** sim10 = new double*[N];
	for (int i = 0; i < N; ++i) {
		sim10[i] = Q1.stockPathFactory();
	}
	matrix_to_file(sim10, 10, dim, "10m.csv");
	
	delete[] stock_path;
	return 0;
}
