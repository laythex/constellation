#include "Satellite.hpp"

Vector Satellite::getPosition() const {
    return kepler.convertToRV();
}

bool Satellite::isTargetVisible(Vector target) const {
    Vector pos = getPosition();
    Vector dir = target - pos;
    double tMin = -pos.dot(dir) / dir.dot(dir);
    double dMin = (pos + dir * tMin).getMagnitude();
    
    if (dMin > Constants::EARTH_RADIUS + Constants::ATMO_HEIGHT) return true;
    if (tMin < 0 || tMin > 1) return true;

    return false;
}

bool Satellite::isTargetVisible(Satellite target) const {
    return isTargetVisible(target.getPosition());
}

double Satellite::getDistance(Vector target) const {
    return (getPosition() - target).getMagnitude();
}

double Satellite::getDistance(Satellite target) const {
    return getDistance(target.getPosition());
}

long long int Satellite::getId() const { return id; }

Kepler& Satellite::getKepler() { return kepler; }

bool Satellite::operator==(Satellite other) const {
    return id == other.getId();
}

bool Satellite::operator!=(Satellite other) const {
    return id != other.getId();
}
