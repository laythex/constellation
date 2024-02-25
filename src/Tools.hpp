#pragma once

#include "Constants.hpp"

class Tools {
public:
	static int rand_uns(int min, int max);
	
	static float constrainAngle(float angle);

	static std::string formatString(long long n);
};

