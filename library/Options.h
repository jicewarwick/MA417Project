#ifndef OPTIONS_H_YOZWBTFN
#define OPTIONS_H_YOZWBTFN

#include <vector>
#include "Model.h"

double EuropeanCallVal(Model* m, std::vector<double> K);
double EuropeanPutVal(Model* m, std::vector<double> K);

bool isDownAccrossTheBarrier(double* path, int dim, double B);
bool isUpAccrossTheBarrier(double* path, int dim, double B);

double DownAndOutCallVal(Model* m, std::vector<double> KB);
double DownAndInCallVal(Model* m, std::vector<double> KB);
double UpAndOutCallVal(Model* m, std::vector<double> KB);
double UpAndInCallVal(Model* m, std::vector<double> KB);

double DownAndOutPutVal(Model* m, std::vector<double> KB);
double DownAndInPutVal(Model* m, std::vector<double> KB);
double UpAndOutPutVal(Model* m, std::vector<double> KB);
double UpAndInPutVal(Model* m, std::vector<double> KB);

#endif /* end of include guard: OPTIONS_H_YOZWBTFN */

