#pragma once

#include "Constants.hpp"
#include "Vector.hpp"
#include "Satellite.hpp"

const unsigned int DEPTH = 20;
const float INF = std::numeric_limits<float>::infinity();

class Constellation {
public:
    Constellation(std::vector<Satellite> sats);
    Constellation();

    void advanceTimeSecs(float s);

    std::vector<Vector> sendRequest(float lat1, float lon1, float lat2, float lon2);
    
    Satellite& operator[](int i);

    std::vector<Satellite> sats;

private:
    void findRecipient(Satellite current, Vector target, unsigned int step, float distance, float& minDistance,
                       std::vector<Satellite>& route, std::vector<Satellite>& shortestRoute);
};
