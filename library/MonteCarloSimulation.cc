#include "MonteCarloSimulation.h"
#include <thread>

void sim_wrapper(MonteCarloSimulation*, int);

MonteCarloSimulation::MonteCarloSimulation (Model* m, std::vector<double> val_arg, std::function<double (Model*, std::vector<double>)> f, int N_sim){
	m_ = m;
	val_arg_ = val_arg;
	f_ = f;
	N_sim_ = N_sim;
	data_ = new double[N_sim_];
	results_ = 0;
}

MonteCarloSimulation::~MonteCarloSimulation(){
	delete[] data_;
}

void MonteCarloSimulation::exec(){
	double tmp_sum = 0;
	// initialise and start threads
	std::thread* t = new std::thread[N_sim_];
	for (int i = 0; i < N_sim_; ++i) {
		t[i] = std::thread(sim_wrapper, this, i);
	}
	
	// wait for them to finish
	for (int i = 0; i < N_sim_; ++i) {
		t[i].join();
	}
/*
	for (int i = 0; i < N_sim_; ++i) {
		data_[i] = f_(m_, val_arg_);
	}
*/
	for (int i = 0; i < N_sim_; ++i) {
		tmp_sum += data_[i];
	}
	results_ = tmp_sum / N_sim_;
}

void MonteCarloSimulation::sim(int i){
	data_[i] = f_(m_, val_arg_);
}

void sim_wrapper(MonteCarloSimulation* m, int i){
	m->sim(i);
}
