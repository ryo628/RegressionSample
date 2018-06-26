#include "Food.hpp"

Food::Food()
{
	// nothing to do
}

Food::Food( std::string s, double d1, double d2, double d3 )
{
	this->name		= s;
	this->carbon	= d1;
	this->fat		= d2;
	this->calorie	= d3;
}

Food::std::string getName()
{
	return this->name;
}

double getCarbon()
{
	return this->carbon;
}

double getFat()
{
	return this->fat;
}

double getCalorie()
{
	return this->calorie;
}
