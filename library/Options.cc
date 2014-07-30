#include "Options.h"
#include <algorithm>


double EuropeanCallVal(Model* m, std::vector<double> K){
	double ST = m->get_ST();
	return (std::max(ST-K[0], 0.0));
}

double EuropeanPutVal(Model* m, std::vector<double> K){
	double ST = m->get_ST();
	return (std::max(K[0]-ST, 0.0));
}

bool isDownAccrossTheBarrier(double* path, int dim, double Barrier){
	for (int i = 0; i < dim; ++i) {
		if (path[i] < Barrier){
			return true;
		}
	}
	return false;
}

bool isUpAccrossTheBarrier(double* path, int dim, double Barrier){
	for (int i = 0; i < dim; ++i) {
		if (path[i] > Barrier){
			return true;
		}
	}
	return false;
}


double DownAndOutPutVal(Model* m, std::vector<double> KB){
	double* path = m->PathFactory();
	int dim = m->get_dim();
	if (isDownAccrossTheBarrier(path, dim, KB[1])) {
		delete[] path;
		return 0.0;
	}
	double ret = std::max(KB[0] - path[dim-1], 0.0);
	delete[] path;
	return ret;
}

double DownAndInPutVal(Model* m, std::vector<double> KB){
	double* path = m->PathFactory();
	int dim = m->get_dim();
	if (!isDownAccrossTheBarrier(path, dim, KB[1])) {
		delete[] path;
		return 0.0;
	}
	double ret = std::max(KB[0] - path[dim-1], 0.0);
	delete[] path;
	return ret;
}

double UpAndOutPutVal(Model* m, std::vector<double> KB){

	double* path = m->PathFactory();
	int dim = m->get_dim();
	if (isUpAccrossTheBarrier(path, dim, KB[1])) {
		delete[] path;
		return 0.0;
	}
	double ret = std::max(KB[0] - path[dim-1], 0.0);
	delete[] path;
	return ret;
}

double UpAndInPutVal(Model* m, std::vector<double> KB){
	double* path = m->PathFactory();
	int dim = m->get_dim();
	if (!isDownAccrossTheBarrier(path, dim, KB[1])) {
		delete[] path;
		return 0.0;
	}
	double ret = std::max(KB[0] - path[dim-1], 0.0);
	delete[] path;
	return ret;
}

double DownAndOutCallVal(Model* m, std::vector<double> KB){
	double* path = m->PathFactory();
	int dim = m->get_dim();
	if (isDownAccrossTheBarrier(path, dim, KB[1])) {
		delete[] path;
		return 0.0;
	}
	double ret = std::max(KB[0] - path[dim-1], 0.0);
	delete[] path;
	return ret;
}

double DownAndInCallVal(Model* m, std::vector<double> KB){
	double* path = m->PathFactory();
	int dim = m->get_dim();
	if (!isDownAccrossTheBarrier(path, dim, KB[1])) {
		delete[] path;
		return 0.0;
	}
	double ret = std::max(KB[0] - path[dim-1], 0.0);
	delete[] path;
	return ret;
}

double UpAndOutCallVal(Model* m, std::vector<double> KB){

	double* path = m->PathFactory();
	int dim = m->get_dim();
	if (isUpAccrossTheBarrier(path, dim, KB[1])) {
		delete[] path;
		return 0.0;
	}
	double ret = std::max(KB[0] - path[dim-1], 0.0);
	delete[] path;
	return ret;
}

double UpAndInCallVal(Model* m, std::vector<double> KB){
	double* path = m->PathFactory();
	int dim = m->get_dim();
	if (!isUpAccrossTheBarrier(path, dim, KB[1])) {
		delete[] path;
		return 0.0;
	}
	double ret = std::max(KB[0] - path[dim-1], 0.0);
	delete[] path;
	return ret;
}
