#include <cmath>
#include "Constellation.hpp"

void Constellation::advanceTime(double deltaTime) {
    for (Orbit& orbit : orbits) {
        orbit.advanceTime(deltaTime);
    }

    if (isSelecting) {
        selectionOrbit.advanceTime(deltaTime);
    }
}

void Constellation::decayOrbits(double deltaTime) {
    for (auto orbit = orbits.begin(); orbit != orbits.end(); orbit++) {
        orbit->decay(deltaTime);

        if (orbit->getIsDecayed()) {
            orbits.erase(orbit);
        }
    }
}

void Constellation::updateSelectionOrbit(Kepler delta, int deltaSatCount) {
    // Обновляем селорбиту (input) 
    selectionOrbit.changeKepler(delta);
    selectionOrbit.changeSatCount(deltaSatCount);
}

bool Constellation::handleLaunchKeys(bool isSelectKeyPressed, bool isLaunchKeyPressed, unsigned long long balance) {
    // Начало selectionа
    if (isSelectKeyPressed && !isSelecting) {
        isSelecting = true;

        selectionOrbit.reset();

        selectionOrbit.addSatellite();
    }

    // Запуск
    if (isLaunchKeyPressed  && isSelecting) {
        isSelecting = false;

        if (balance > getLaunchPrice()) {
            
            // Создать орбиту из селорбиты
            Orbit orbit(selectionOrbit.getKepler());
            orbit.setSatellites(selectionOrbit.getSatellites());
            orbits.push_back(orbit);

            return true;
        }
    }

    return false;
}

unsigned long long Constellation::getLaunchPrice() const {
    return selectionOrbit.calculateLaunchPrice();
}

/*
std::vector<Vector> Constellation::sendRequest(double lat1, double lon1, double lat2, double lon2) {
    double x1 = Constants::EARTH_RADIUS * cos(lat1) * cos(lon1);
    double y1 = Constants::EARTH_RADIUS * cos(lat1) * sin(lon1);
    double z1 = Constants::EARTH_RADIUS * sin(lat1);
    Vector origin(-x1, y1, z1);
    double x2 = Constants::EARTH_RADIUS * cos(lat2) * cos(lon2);
    double y2 = Constants::EARTH_RADIUS * cos(lat2) * sin(lon2);
    double z2 = Constants::EARTH_RADIUS * sin(lat2);
    Vector target(-x2, y2, z2);

    std::vector<Satellite> route, minRoute;
    double minDistance = INF;

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

void Constellation::findRecipient(Satellite current, Vector target, unsigned int step, double distance, double& minDistance,
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

        double deltaDistance = current.getDistance(sat);
        findRecipient(sat, target, step + 1, distance + deltaDistance, minDistance, route, minRoute);
        route.pop_back();
    }
}
*/
void Constellation::draw(sf::RenderWindow& window) const {
    for (const Orbit& orbit : orbits) {
        orbit.draw(window);
    }

    /*
    for (auto& sat : net.sats) {
        double theta1 = -1, theta2 = -1, dtheta, theta;
        bool prev = false, curr = false;
        int dir = 0;

        Kepler kep = sat.getKepler();
        Vector pos;
        for (double theta = 0; theta < 2 * Constants::PI; theta += 2 * Constants::PI / Constants::DETAIL) {

            kep.ta = theta;
            pos = kep.convertToRV() * Constants::SCALE_FACTOR;

            curr = !(pos.getY() < 0 && pos.getX() * pos.getX() + pos.getZ() * pos.getZ() < Constants::EARTH_RADIUS_ON_SCREEN * Constants::EARTH_RADIUS_ON_SCREEN);
            if (theta == 0) {
                prev = curr;
                continue;
            }

            if (curr != prev) {
                if (theta1 == -1) theta1 = theta;
                else if (theta2 == -1) theta2 = theta;
                else break;
            }

            prev = curr;
        }

        sf::VertexArray orbit(sf::LineStrip, Constants::DETAIL);

        dtheta = std::max(theta2 - theta1, 2 * Constants::PI - theta2 + theta1);
        dir = 2 * (theta2 - theta1 > Constants::PI) - 1;

        for (int i = 0; i < Constants::DETAIL; i++) {
            theta = theta1 + dir * dtheta / Constants::DETAIL * i;

            kep.ta = theta;
            pos = kep.convertToRV() * Constants::SCALE_FACTOR;

            orbit[i].position = sf::Vector2f(pos.getX(), -pos.getZ());

            if (isSelectionNet)
                orbit[i].color = Constants::SELECTION_ORBIT_COLOR;
            else
                orbit[i].color = Constants::DEFAULT_ORBIT_COLOR;
        }

        window.draw(orbit);

        sf::CircleShape satellite(Constants::SATELLITE_RADIUS);

        satellite.setFillColor(Constants::SATELLITE_COLOR);
        satellite.setOrigin(Constants::SATELLITE_RADIUS, Constants::SATELLITE_RADIUS);

        kep = sat.getKepler();
        pos = kep.convertToRV() * Constants::SCALE_FACTOR;
        satellite.setPosition(pos.getX(), -pos.getZ());
        if (!(pos.getY() < 0 && pos.getX() * pos.getX() + pos.getZ() * pos.getZ() < Constants::EARTH_RADIUS_ON_SCREEN * Constants::EARTH_RADIUS_ON_SCREEN))
            window.draw(satellite);
    }
    */
}


