#pragma once

#include <cmath>

#include "Constants.hpp"
#include "Vector.hpp"

class Kepler {
	public:
	double sma, inc, raan;

	Kepler();
	Kepler(double sma, double inc, double raan);

	Vector convertToRV(double ta) const;

	double calculateOrbitalPeriod() const;
};
