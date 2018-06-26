#ifndef FOOD_H
#define FOOD_H

class Food
{
private:
	std::string name;
	double carbon;
	double fat;
	double calorie;

public:
	Food(){}
	Food( std::string s, double d1, double d2, double d3 )
	{
		this->name		= s;
		this->carbon	= d1;
		this->fat		= d2;
		this->calorie	= d3;
	}

	std::string getName(){ return this->name; }
	double getCarbon(){ return this->carbon; }
	double getFat(){ return this->fat; }
	double getCalorie(){ return this->calorie; }
};

#endif