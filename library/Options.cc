#include "Options.h"
#include <algorithm>


double EuropeanCallVal(double St, double K){
	return (std::max(St-K, 0.0));
}
