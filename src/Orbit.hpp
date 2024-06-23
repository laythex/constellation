#pragma once

#include "Constants.hpp"
#include "Vector.hpp"
#include "Kepler.hpp"
#include "Satellite.hpp"

class Orbit {
    public:

    Orbit(Kepler kepler);

    void setKepler(Kepler newKepler);
    Kepler getKepler() const;

    void setSatellites(std::vector<std::pair<Satellite, double>> sats);
    std::vector<std::pair<Satellite, double>> getSatellites() const;

    bool getIsDecayed() const;

    void advanceTime(double deltaTime);

    void decay(double deltaTime);

    void draw(sf::RenderWindow window) const;

    private:

    std::pair<double, double> calculateUnobstructedOrbitSegment() const;
    Vector calculateFlatPosition(double phi) const;

    Kepler kepler;
    std::vector<std::pair<Satellite, double>> satellites;
    bool isDecayed;
};