#ifndef DATAEXPORT_H_CVJ7C5R1
#define DATAEXPORT_H_CVJ7C5R1

#include <string>

void array_to_file(double* data, int n_col, std::string filename);
void matrix_to_file(double** data, int n_row, int n_col, std::string filename);

#endif /* end of include guard: DATAEXPORT_H_CVJ7C5R1 */

