/******************************************************
kadai3.cpp
name : Ryotaro SUMI
number : 183342
TODO
******************************************************/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "Food.h"
#include "Regression.hpp"

/* split */
std::vector<std::string> split( std::string& input, char delimiter )
{
	std::istringstream stream(input);
	std::string field;
	std::vector<std::string> result;
	while( getline( stream, field, delimiter ) )
	{
		result.push_back(field);
	}

	// return
	return result;
}

int main( int argc, char** argv )
{
	std::ifstream ifs( argv[1] );	// ifs
	std::string line;				// tmp string
	std::vector<Food> foods;		// food list

	// csv read
	getline( ifs, line );
	while( getline(ifs, line) )
	{
		// split read line
		std::vector<std::string> strvec = split(line, ',');

		// 
		foods.push_back( Food( strvec[0],
							   std::stod( strvec[2] ),
							   std::stod( strvec[4] ),
							   std::stod( strvec[3] )
							 )
		);
	}

	return 0;
}