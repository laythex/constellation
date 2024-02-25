#include <cmath>

#include "Satellite.hpp"
#include "Kepler.hpp"

Satellite::Satellite() : id(0), kepler(Kepler()) { }
Satellite::Satellite(long long int id, Kepler kepler) : id(id), kepler(kepler) { }

Vector Satellite::getPosition() const {
    return kepler.convertToRV();
}

bool Satellite::isTargetVisible(Vector target) const {
    Vector pos = getPosition();
    Vector dir = target - pos;
    float tMin = -pos.dot(dir) / dir.dot(dir);
    float dMin = (pos + dir * tMin).getMagnitude();
    
    if (dMin > Constants::EARTH_RADIUS + Constants::ATMO_HEIGHT) return true;
    if (tMin < 0 || tMin > 1) return true;

    return false;
}

bool Satellite::isTargetVisible(Satellite target) const {
    return isTargetVisible(target.getPosition());
}

float Satellite::getDistance(Vector target) const {
    return (getPosition() - target).getMagnitude();
}

float Satellite::getDistance(Satellite target) const {
    return getDistance(target.getPosition());
}

void Satellite::advanceTimeSecs(float s) {
    float T = 2 * Constants::PI * sqrt(kepler.sma * kepler.sma * kepler.sma / Constants::EARTH_MU);
    kepler.ta += 2 * Constants::PI * s / T;
    if (kepler.ta > 2 * Constants::PI) kepler.ta -= 2 * Constants::PI;
}

long long int Satellite::getId() const { return id; }

Kepler& Satellite::getKepler() { return kepler; }

bool Satellite::operator==(Satellite other) const {
    return id == other.getId();
}

bool Satellite::operator!=(Satellite other) const {
    return id != other.getId();
}
