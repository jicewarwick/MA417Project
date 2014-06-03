#include "MonteCarloSimulation.h"
#include <thread>

void sim_wrapper(MonteCarloSimulation*, int);

MonteCarloSimulation::MonteCarloSimulation (double (*f)(), int N_sim): N_sim_(N_sim){
	f_ = f;
	data_ = new double[N_sim_];
	results_ = 0;
}

MonteCarloSimulation::~MonteCarloSimulation(){
	delete[] data_;
}

void MonteCarloSimulation::exec(){
	double tmp_sum = 0;
	std::thread* t = new std::thread[N_sim_];
	for (int i = 0; i < N_sim_; ++i) {
		t[i] = std::thread(sim_wrapper, this, i);
	}

	for (int i = 0; i < N_sim_; ++i) {
		t[i].join();
	}

	for (int i = 0; i < N_sim_; ++i) {
		tmp_sum += data_[i];
	}
	results_ = tmp_sum / N_sim_;
}


void MonteCarloSimulation::sim(int i){
	data_[i] = f_();
}
void sim_wrapper(MonteCarloSimulation* m, int i){
	m->sim(i);
}
