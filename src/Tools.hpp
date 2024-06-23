#pragma once

#include "Constants.hpp"

class Tools {
public:
	static int rand_uns(int min, int max);
	
	static double constrainAngle(double angle, double cap);

	static std::string formatString(long long n);
};

