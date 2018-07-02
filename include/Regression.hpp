#ifndef REGRESSION_H
#define REGRESSION_H

#include <vector>
#include <functional>
#include <iostream>
#include "Food.hpp"

class Regression
{
private:
	double a;						// Regression coefficient
	double b;						// Regression intercept
	double R2;						// contribution rate
	double xmean;					// mean
	double ymean;					// mean
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
	void compMean( double (Food::*getter)() );	// calculate xmean and ymean
	void doRegression( std::string );			// regression

	// calculate deviation
	double deviation( std::function<double(int)> f, int start, int end );
	// predict from a, b
	double calcPredicted( Food f, std::string _s );
};

#endif