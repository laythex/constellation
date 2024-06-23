#pragma once

class SelectionOrbit : public Orbit {

    public:

    SelectionOrbit(Kepler kepler);

    void changeKepler(Kepler delta);
    void changeSatCount(int deltaSatCount);

    void addSatellite();
    void removeSatellite();

    void reset();

    unsigned long long calculateLaunchPrice() const;
};