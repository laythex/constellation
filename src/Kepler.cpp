#include <cmath>

#include "Kepler.hpp"

Kepler::Kepler() : Kepler(0, 0, 0, 0) {}
Kepler::Kepler(float sma, float inc, float raan, float ta) : sma(sma), inc(inc), raan(raan), ta(ta) {}

Vector Kepler::convertToRV() const {

    float x = sma * (cos(raan) * cos(ta) - sin(raan) * sin(ta) * cos(inc));
    float y = sma * (sin(raan) * cos(ta) + cos(raan) * sin(ta) * cos(inc));
    float z = sma * sin(inc) * sin(ta);

    return Vector(x, y, z);
}