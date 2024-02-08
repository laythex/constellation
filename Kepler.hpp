#pragma once

#include "Constants.hpp"
#include "Vector.hpp"

class Kepler {
public:
	float sma, inc, raan, ta;

	Kepler();
	Kepler(float sma, float inc, float raan, float ta);

	Vector convertToRV() const;
};
