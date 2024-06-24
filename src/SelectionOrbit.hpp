#pragma once

#include "Orbit.hpp"

class SelectionOrbit : public Orbit {

    public:

    SelectionOrbit();

    void changeKepler(Kepler delta);
    void changeSatCount(int deltaSatCount);

    void addSatellite();
    void removeSatellite();

    void reset();

    unsigned long long calculateLaunchPrice() const;
};