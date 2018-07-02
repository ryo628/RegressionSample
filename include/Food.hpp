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
	double gi;
	double protain;

public:
	/* constructor */
	Food();
	Food( std::string s, double d1, double d2, double d3 );
	Food( std::string s, double d1, double d2, double d3, double d4, double d5 );

	/* accessor */
	std::string getName();
	double getCarbon();
	double getFat();
	double getCalorie();
	double getGI();
	double getProtain();
};

#endif