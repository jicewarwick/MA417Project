#include "HestonModel.h"
#include <ctime>
#include <cmath>
#include <algorithm>

HestonModel::HestonModel(double alpha, double beta, double gamma, double rho, double v0, double r, double S0, double T, int N_int, NormalRandomNumberGenerator* norm_gen) : Model(){
	alpha_	= alpha;
	beta_	= beta;
	gamma_ 	= gamma;
	rho_	= rho;
	v0_		= v0;
	r_		= r;
	S0_		= S0;
	T_		= T;
	N_int_ 	= N_int;
	dim_	= T * N_int_ + 1;
	norm_gen_ = norm_gen;
}

double* HestonModel::volativityPathFactory(double*& db1){
	db1 = new double[dim_-1];
	double *volativity_path = new double[dim_];
	volativity_path[0] = v0_;
	double tmp_sqrt_N_int_ = sqrt(N_int_);

	for (int i = 0; i < dim_-1; ++i) {
		db1[i] = norm_gen_->getNormalRandomVariable();
		volativity_path[i+1] = volativity_path[i] + alpha_ * (beta_ - volativity_path[i]) / N_int_ + gamma_ * sqrt(volativity_path[i]) * db1[i] / tmp_sqrt_N_int_;
	}
	return volativity_path;
}

double* HestonModel::PathFactory(){
	double* db1;
	double* db2 = new double[dim_-1];
	double* volativity_path = volativityPathFactory(db1);
	double* stock_path = new double[dim_];
	stock_path[0] = log(S0_);
	double anti_corr = sqrt(1-pow(rho_, 2));
	double tmp_sqrt_N_int_ = sqrt(N_int_);

	for (int i = 0; i < dim_-1; ++i) {
		db2[i] = norm_gen_->getNormalRandomVariable();
		stock_path[i+1] = stock_path[i] + std::max(r_-0.5*volativity_path[i], 0.0) / N_int_ + sqrt(volativity_path[i])*(rho_*db1[i] + anti_corr * db2[i])/tmp_sqrt_N_int_;
	}

	for (int i = 0; i < dim_; ++i) {
		stock_path[i] = exp(stock_path[i]);
	}

	delete[] db1;
	delete[] db2;
	delete[] volativity_path;

	return stock_path;
		
}

double HestonModel::get_ST(){
	double* stock_path = PathFactory();
	double ret = stock_path[dim_-1];
	delete[] stock_path;
	return ret;
}

double HestonModel::get_path_mean(){
	double* stock_path = PathFactory();
	double tmp_sum = 0;
	for (int i = 0; i < dim_; ++i) {
		tmp_sum += stock_path[i];
	}
	delete[] stock_path;
	double ret = tmp_sum / dim_;
	return ret;
}
