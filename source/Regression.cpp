#include "Regression.hpp"

/* constructor */
Regression::Regression( std::vector<Food> _data, std::string _labels )
{
	this->a = 0;
	this->b = 0;
	this->R2 = 0;
	this->xmean = 0;
	this->ymean = 0;
	this->data = _data;
	this->labels = _labels;

	// put size
	this->samples = this->data.size();

	// calc means
	this->compMean();
}

/* accessor */
double Regression::getA(){ return this->a; }
double Regression::getB(){ return this->b; }
double Regression::getR2(){ return this->R2; }

/* calc xmean and ymean */
void Regression::compMean()
{
	double xsum = 0;
	double ysum = 0;

	// sum loop
	for( auto d : this->data )
	{
		xsum += d.getCarbon();
		ysum += d.getCalorie();
	}

	this->xmean = xsum / this->samples;
	this->ymean = ysum / this->samples;
}

/* calc deviation */
double Regression::deviation( std::function<double(int)> f, int start, int end )
{
	double sum = 0;

	for( int i = start; i < end; i++ )
	{
		sum += f(i);
	}

	return sum;
}

double Regression::calcPredicted( Food f )
{
	// predict Carbon
	return this->a * f.getCarbon() + this->b;
}

/* do regression */
void Regression::doRegression()
{
	// calc Sxx, Syy and Sxy
	double Sxx = this->deviation(
						[&](int i)
						{
							return ( this->data[i].getCarbon() - this->xmean )*
									( this->data[i].getCarbon() - this->xmean );
						},
						0,
						this->samples
	);
	double Syy = this->deviation(
						[&](int i)
						{
							return ( this->data[i].getCalorie() - this->ymean )*
									( this->data[i].getCalorie() - this->ymean );
						},
						0,
						this->samples
	);
	double Sxy = this->deviation(
						[&](int i)
						{
							return ( this->data[i].getCarbon() - this->xmean )*
									( this->data[i].getCalorie() - this->ymean );
						},
						0,
						this->samples
	);

	// calc a, b
	this->a = Sxy / Sxx;
	this->b = this->ymean - this->a*this->xmean;

	/* calc R2 */
	// calc predict mean
	for( int i; i < this->samples; i++ )
	{
		this->predicted.push_back( this->calcPredicted( this->data[i] ) );
	}
	double pMean = 0;
	for( double d : this->predicted ) pMean += d;
	pMean = pMean / (double)this->predicted.size();

	// calc Re denominator
	double d2 = this->deviation(
						[&](int i)
						{
							return ( this->predicted[i] - pMean )*
									( this->predicted[i] - pMean );
						},
						0,
						this->samples
	);
	double n1 = this->deviation(
						[&](int i)
						{
							return ( this->data[i].getCalorie() - this->ymean )*
									( this->predicted[i] - pMean );
						},
						0,
						this->samples
	);
	this->R2 = ( n1 * n1 ) / ( Syy * d2 );
}