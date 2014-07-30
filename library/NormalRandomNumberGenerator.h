#ifndef NORMALRANDOMNUMBERGENERATOR_H_LAXVOXJG
#define NORMALRANDOMNUMBERGENERATOR_H_LAXVOXJG

#include <boost/random.hpp>
#include <boost/random/variate_generator.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/normal_distribution.hpp>

class NormalRandomNumberGenerator {
public:
	NormalRandomNumberGenerator();
	virtual ~NormalRandomNumberGenerator(){}
	double getNormalRandomVariable();

private:
	boost::mt19937 rng;
    boost::normal_distribution<double> dist_normal;
    boost::variate_generator<boost::mt19937&, boost::normal_distribution<double> > rand_normal;

};
#endif /* end of include guard: NORMALRANDOMNUMBERGENERATOR_H_LAXVOXJG */

