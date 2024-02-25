#include <cmath>
#include "Constellation.hpp"

Constellation::Constellation(std::vector<Satellite> sats) : sats(sats) { }

Constellation::Constellation() { }

void Constellation::advanceTimeSecs(float s) {
    for (auto& sat : sats) {
        sat.advanceTimeSecs(s);
    }
}

Satellite& Constellation::operator[](int i) {
    return sats[i];
}

std::vector<Vector> Constellation::sendRequest(float lat1, float lon1, float lat2, float lon2) {
    float x1 = Constants::EARTH_RADIUS * cos(lat1) * cos(lon1);
    float y1 = Constants::EARTH_RADIUS * cos(lat1) * sin(lon1);
    float z1 = Constants::EARTH_RADIUS * sin(lat1);
    Vector origin(-x1, y1, z1);
    float x2 = Constants::EARTH_RADIUS * cos(lat2) * cos(lon2);
    float y2 = Constants::EARTH_RADIUS * cos(lat2) * sin(lon2);
    float z2 = Constants::EARTH_RADIUS * sin(lat2);
    Vector target(-x2, y2, z2);

    std::vector<Satellite> route, minRoute;
    float minDistance = INF;

    Satellite originSat(0, Kepler(Constants::EARTH_RADIUS, Constants::PI / 2, lon1, lat1));
    findRecipient(originSat, target, 0, 0, minDistance, route, minRoute);

    std::vector<Vector> path;
    path.push_back(origin);
    for (auto& e : minRoute) {
        path.push_back(e.getPosition());
    }
    path.push_back(target);

    return path;
}

void Constellation::findRecipient(Satellite current, Vector target, unsigned int step, float distance, float& minDistance,
                                  std::vector<Satellite>& route, std::vector<Satellite>& minRoute) {
    if (step > DEPTH) return;

    if (current.isTargetVisible(target)) {
        distance += current.getDistance(target);
        if (distance < minDistance) {
            minRoute = route;
            minDistance = distance;
        }
        return;
    }

    for (auto& sat : sats) {

        if (sat == current) continue;

        bool isAlreadyInRoute = false;
        for (auto& inRouteSat : route) {
            if (inRouteSat == sat) {
                isAlreadyInRoute = true;
                break;
            }
        }

        if (isAlreadyInRoute) continue;

        if (step > 0 && sat.getDistance(target) > current.getDistance(target)) continue;

        if (!current.isTargetVisible(sat)) continue;

        route.push_back(sat);

        float deltaDistance = current.getDistance(sat);
        findRecipient(sat, target, step + 1, distance + deltaDistance, minDistance, route, minRoute);
        route.pop_back();
    }
}
