/******************************************************
kadai3.cpp
name : Ryotaro SUMI
number : 183342
単回帰でカロリーを予測する
2018-07-02 22:14:27
******************************************************/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

#include "Food.hpp"
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
	std::string line;					// tmp string
	std::vector<Food> foods;			// food list
	std::map<char, std::string> flags;	// flags list
	flags['G'] = "GI";
	flags['C'] = "Carbon";
	flags['F'] = "Fat";
	flags['P'] = "Protain";

	// arg check
	if( argc != 3 )
	{
		std::cout << "Error : missing argument" << std::endl;
		return -1;
	}

	// data read
	std::ifstream ifs( argv[1] );
	getline( ifs, line );
	while( getline(ifs, line) )
	{
		// split read line
		std::vector<std::string> strvec = split( line, ',' );

		// 
		foods.push_back( Food( strvec[0],
							   std::stod( strvec[2] ),
							   std::stod( strvec[4] ),
							   std::stod( strvec[1] ),
							   std::stod( strvec[5] ),
							   std::stod( strvec[3] )
							 )
		);
	}
	ifs.close();

	// flag check
	char flag = argv[2][0];
	if( flags.find( flag ) == flags.end() )
	{
		std::cout << "Error : flag error" << std::endl;
		return -1;
	}

	// regression
	Regression r = Regression( foods, "calorie" );
	std::string flagName = flags[flag];
	r.doRegression( flagName );

	// result
	std::cout << flagName << " → " << r.getLabels() << std::endl;
	std::cout << "a : " << r.getA() << std::endl;
	std::cout << "b : " << r.getB() << std::endl;
	std::cout << "R2 : " << r.getR2() << std::endl;

	// predict
	// [A] さくらんぼ（炭水化物=15.2, たんぱく質=1.0, GI=37, 脂質=0.2）
	Food a = Food( "さくらんぼ", 15.2, 0.2, 37, 1.0, 0 );
	std::cout << "[A] " << a.getName() << " : " << r.calcPredicted( a, flagName ) << " kcal" << std::endl;
	// [B] バジル（炭水化物=4.0, たんぱく質=2.0, GI=5, 脂質=0.6）
	Food b = Food( "バジル", 4.0, 0.6, 5, 2.0, 0 );
	std::cout << "[B] " << b.getName() << " : " << r.calcPredicted( b, flagName ) << " kcal" << std::endl;
	// [C] 豆乳（炭水化物=3.1, たんぱく質=3.6,GI=23, 脂質=2.0）
	Food c = Food( "豆乳", 3.1, 0.2, 23, 3.6, 0 );
	std::cout << "[C] " << c.getName() << " : " << r.calcPredicted( c, flagName ) << " kcal" << std::endl;

	return 0;
}