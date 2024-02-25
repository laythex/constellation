#pragma once

#include "Constants.hpp"
#include "Vector.hpp"
#include "Kepler.hpp"

class Satellite {
public:
    Satellite();
    Satellite(long long int id, Kepler kepler);

    Vector getPosition() const;

    bool isTargetVisible(Vector target) const;
    bool isTargetVisible(Satellite target) const;

    float getDistance(Vector target) const;
    float getDistance(Satellite target) const;

    void advanceTimeSecs(float s);

    long long int getId() const;
    Kepler& getKepler();

    bool operator==(Satellite other) const;
    bool operator!=(Satellite other) const;

private:
    long long int id;
    Kepler kepler;
};
