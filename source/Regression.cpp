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
}

/* accessor */
double Regression::getA(){ return this->a; }
double Regression::getB(){ return this->b; }
double Regression::getR2(){ return this->R2; }
std::string Regression::getLabels(){ return this->labels; }

/* calc xmean and ymean */
void Regression::compMean( double (Food::*getter)() )
{
	double xsum = 0;
	double ysum = 0;

	// sum loop
	for( Food d : this->data )
	{
		xsum += (d.*getter)();
		ysum += d.getCalorie();
	}

	// comp mean
	this->xmean = xsum /  this->samples;
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

/* predict Food Calorie */
double Regression::calcPredicted( Food f, std::string _s )
{
	// switch predict
	if( _s == "Carbon" )
		return this->a * f.getCarbon() + this->b;
	else if( _s == "Fat" )
		return this->a * f.getFat() + this->b;
	else if( _s == "GI" )
		return this->a * f.getGI() + this->b;
	else if ( _s == "Protain" )
		return this->a * f.getProtain() + this->b;
	else
		return this->a * f.getCarbon() + this->b;
}


/* do regression */
void Regression::doRegression( std::string _s )
{
	// switch getter
	double ( Food::*getter )();
	if( _s == "Carbon" )
		getter = &Food::getCarbon;
	else if( _s == "Fat" )
		getter = &Food::getFat;
	else if( _s == "GI" )
		getter = &Food::getGI;
	else if ( _s == "Protain" )
		getter = &Food::getProtain;
	else
		getter = &Food::getCarbon;

	// calc means
	this->compMean( getter );

	// calc Sxx and Sxy
	double Sxx = this->deviation(
					[&](int i)
					{
						return ( ( this->data[i].*getter )() - this->xmean )*
								( ( this->data[i].*getter )() - this->xmean );
					},
					0,
					this->samples
	);
	double Sxy = this->deviation(
					[&](int i)
					{
						return ( ( this->data[i].*getter )() - this->xmean )*
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
		// predict input data
		this->predicted.push_back(
			this->a * (this->data[i].*getter)() + this->b
		);
	}
	double pMean = 0;
	for( double d : this->predicted ) pMean += d;
	pMean = pMean / (double)this->predicted.size();

	// calc R2 denominator
	double d1 = this->deviation(
						[&](int i)
						{
							return ( this->data[i].getCalorie() - this->ymean )*
									( this->data[i].getCalorie() - this->ymean );
						},
						0,
						this->samples
	);
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
	this->R2 = ( n1 * n1 ) / ( d1 * d2 );
}