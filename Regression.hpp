#ifndef REGRESSION_H
#define REGRESSION_H

#include <vector>
#include "Food.h"

class Regression
{
private:
	double a;						// Regression coefficient
	double b;						// Regression intercept
	double R2;						// contribution rate
	double xmean;					// TODO: mean
	double ymean;					// TODO: mean
	int samples;					// sample num
	std::vector<Food> data;			// input data
	std::string labels;				// labels( calorie )
	std::vector<double> predicted;	// predict value

public:
	/* constructor */
	Regression( std::vector<Food> data, std::string labels );

	/* accessor */
	double getA();
	double getB();
	double getR2();

	/* method */
	void compMean();		// calculate xmean and ymean
	void doRegression();	// regression
};

#endif