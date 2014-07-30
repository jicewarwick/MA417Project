#ifndef HESTONMODEL_H_O6NC2V3Y
#define HESTONMODEL_H_O6NC2V3Y

#include "Model.h"
#include "NormalRandomNumberGenerator.h"

class HestonModel : public Model{
public:
	HestonModel(double alpha, double beta, double gamma, double rho, double v0, double r, double S0, double T, int N_int, NormalRandomNumberGenerator* norm_gen);
	virtual double* PathFactory();
	int get_dim(){return dim_;}
	double get_ST();
	double get_min();
	double get_max();
	double get_path_mean();

	virtual ~HestonModel (){}

private:
	double alpha_;
	double beta_;
	double gamma_;
	double rho_;
	double v0_;
	double r_;
	double S0_;
	double T_;
	int N_int_;
	int dim_;
	NormalRandomNumberGenerator* norm_gen_;

	double* volativityPathFactory(double*& db1);
};


#endif /* end of include guard: HESTONMODEL_H_O6NC2V3Y */

