#include "MonteCarloSimulation.h"
#include <thread>
#include <algorithm>
#include <iostream>

#ifdef SINGLE_THREAD
#define NUM_CORE 1
#else
#define NUM_CORE 2
#endif

void sim_wrapper(MonteCarloSimulation*, int start, int end);

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
		std::cout << "Monte Carlo Simulation using " << NUM_CORE << " cores." << std::endl;
	double tmp_sum = 0;
	// initialise and start threads
	std::thread* t = new std::thread[NUM_CORE];
	int	start = 0;
	int	end = 0;
	int thread_load = std::ceil(N_sim_ /(double) NUM_CORE);
	for (int i = 0; i < NUM_CORE; ++i) {
		start = i * thread_load;
		end = std::min(start + thread_load, N_sim_);
		t[i] = std::thread(sim_wrapper, this, start, end);
	}
	
	// wait for them to finish
	for (int i = 0; i < NUM_CORE; ++i) {
		t[i].join();
	}

	// compute the mean
	for (int i = 0; i < N_sim_; ++i) {
		tmp_sum += data_[i];
	}
	results_ = tmp_sum / N_sim_;
}

void MonteCarloSimulation::sim(int start, int end){
	for (int i = start; i < end; ++i) {
		data_[i] = f_(m_, val_arg_);
	}
}

void sim_wrapper(MonteCarloSimulation* m, int start, int end){
	m->sim(start, end);
}
