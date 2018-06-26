#ifndef FOOD_H
#define FOOD_H

#include <string>

class Food
{
private:
	std::string name;
	double carbon;
	double fat;
	double calorie;

public:
	/* constructor */
	Food(){}
	Food( std::string s, double d1, double d2, double d3 );

	/* accessor */
	std::string getName();
	double getCarbon();
	double getFat();
	double getCalorie();
};

#endif