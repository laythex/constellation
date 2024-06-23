#include <cmath>

#include "Kepler.hpp"

Kepler::Kepler() : Kepler(0, 0, 0) {}
Kepler::Kepler(double sma, double inc, double raan) : sma(sma), inc(inc), raan(raan) {}

Vector Kepler::convertToRV(double ta) const {
    double x = sma * (cos(raan) * cos(ta) - sin(raan) * sin(ta) * cos(inc));
    double y = sma * (sin(raan) * cos(ta) + cos(raan) * sin(ta) * cos(inc));
    double z = sma * sin(inc) * sin(ta);

    return Vector(x, y, z);
}

double Kepler::calculateOrbitalPeriod() const {
    return M_2_PI * sqrt(sma * sma * sma / Constants::EARTH_MU);
}