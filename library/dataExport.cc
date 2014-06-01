#include <fstream>
#include "dataExport.h"


void matrix_to_file(double** data, int n_row, int n_col, std::string filename){
	std::ofstream output(filename);

	if (output.is_open()) {
		for (int i = 0; i < n_row; ++i) {
			output << data[i][0];
			for (int j = 1; j < n_col; ++j) {
				output << ',' << data[i][j];
			}
			output << '\n';
		}
	}
	output.close();
}

void array_to_file(double* data, int n_col, std::string filename){
	double** tmp = new double*[1];
	tmp[0] = data;
	matrix_to_file(tmp, 1, n_col, filename);
}
