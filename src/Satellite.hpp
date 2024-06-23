#pragma once

#include "Constants.hpp"
#include "Vector.hpp"
#include "Kepler.hpp"

class Satellite {
public:
    Vector getPosition() const;

    bool isTargetVisible(Vector target) const;
    bool isTargetVisible(Satellite target) const;

    double getDistance(Vector target) const;
    double getDistance(Satellite target) const;

    long long int getId() const;
    Kepler& getKepler();

    bool operator==(Satellite other) const;
    bool operator!=(Satellite other) const;
};
