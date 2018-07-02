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

Food::Food( std::string s, double d1, double d2, double d3, double d4, double d5 )
{
	this->name		= s;
	this->carbon	= d1;
	this->fat		= d2;
	this->gi		= d3;
	this->protain	= d4;
	this->calorie	= d5;
}


std::string Food::getName()
{
	return this->name;
}

double Food::getCarbon()
{
	return this->carbon;
}

double Food::getFat()
{
	return this->fat;
}

double Food::getCalorie()
{
	return this->calorie;
}

double Food::getGI()
{
	return this->gi;
}

double Food::getProtain()
{
	return this->protain;
}