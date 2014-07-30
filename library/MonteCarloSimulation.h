#ifndef MONTECARLOSIMULATION_H_DAHP1FTK
#define MONTECARLOSIMULATION_H_DAHP1FTK

#include <functional>
#include <vector>
#include "Model.h"

class MonteCarloSimulation {
public:
	MonteCarloSimulation (Model* m, std::vector<double> val_arg, std::function<double (Model*, std::vector<double>)>, int N_sim);
	virtual ~MonteCarloSimulation ();
	void exec();
	double get_results(){return results_;}
	void sim(int i);

private:
	Model* m_;
	std::vector<double> val_arg_;
	std::function<double (Model*, std::vector<double>)> f_;
	double results_;
	int N_sim_;
	double* data_;
};

#endif /* end of include guard: MONTECARLOSIMULATION_H_DAHP1FTK */
