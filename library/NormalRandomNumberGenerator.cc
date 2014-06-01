#include "NormalRandomNumberGenerator.h"
#include <ctime>


NormalRandomNumberGenerator::NormalRandomNumberGenerator():rng(boost::mt19937(time(0))),
                                 dist_normal(boost::normal_distribution<double>(0.0,1.0)),
                                 rand_normal(boost::variate_generator<boost::mt19937&, boost::normal_distribution<double> >(rng, dist_normal)){}

double NormalRandomNumberGenerator::getNormalRandomVariable(){
	return rand_normal();
}
