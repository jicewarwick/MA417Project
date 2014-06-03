#ifndef MONTECARLOSIMULATION_H_DAHP1FTK
#define MONTECARLOSIMULATION_H_DAHP1FTK

class MonteCarloSimulation {
public:
	MonteCarloSimulation (double (*f)(), int N_sim);
	virtual ~MonteCarloSimulation ();
	void exec();
	double getResults(){return results_;}
	void sim(int i);

private:
	double (*f_)();
	double results_;
	int N_sim_;
	double* data_;

};

#endif /* end of include guard: MONTECARLOSIMULATION_H_DAHP1FTK */

