#pragma once

#include "Constants.hpp"
#include "Vector.hpp"
#include "Orbit.hpp"
#include "SelectionOrbit.hpp"

// Пофиксить
const unsigned int DEPTH = 20;
const double INF = 1e150;

class Constellation {
public:
    Constellation();

    void advanceTime(double deltaTime);
    void decayOrbits(double deltaTime);
    void updateSelectionOrbit(Kepler delta, int deltaSatCount);
    bool handleLaunchKeys(bool isSelectKeyPressed, bool isLaunchKeyPressed, unsigned long long balance);

    unsigned long long getLaunchPrice() const;

    // std::vector<Vector> sendRequest(double lat1, double lon1, double lat2, double lon2);

    void draw(sf::RenderWindow& window) const;

    std::vector<Orbit> orbits;
    SelectionOrbit selectionOrbit;

private:
    /*
    void findRecipient(Satellite current, Vector target, unsigned int step, double distance, double& minDistance,
                       std::vector<Satellite>& route, std::vector<Satellite>& shortestRoute);
    */
    std::pair<double, double> calculateUnobstructedOrbitSegment();

    bool isSelecting;
};
