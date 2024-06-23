#include "Orbit.hpp"

Orbit::Orbit(Kepler kepler) : kepler(kepler), isDecayed(false) { }

void Orbit::setKepler(Kepler newKepler) {
    kepler = newKepler;
}

Kepler Orbit::getKepler() const {
    return kepler;
}

void setSatellites(std::vector<std::pair<Satellite, double>> sats) {
    satellites = sat;
}

std::vector<std::pair<Satellite, double>> getSatellites() const {
    return satellites;
}

bool getIsDecayed() const {
    return isDecayed;
}

void Orbit::advanceTime(double deltaTime) {
    double T = kepler.calculateOrbitalPeriod();
    double deltaTa = M_2_PI * deltaTime / T * Constants::SIMULATION_SPEED;

    for (std::pair<Satellite, double>& satellite : satellites) {
        pair.second = Tools::constrainAngle(pair.second + deltaTa);
    }
}

void Orbit::decay(double deltaTime) {
    kepler.sma -= Constants::ORBIT_DECAY_SPEED * deltaTime;

    if (kepler.sma < Constants::EARTH_RADIUS + Constants::ATMO_HEIGHT) {
        isDecayed = true;
    }
}

void Orbit::draw(sf::RenderWindow window) const { 
    
    sf::VertexArray orbitVA(sf::LineStrip, Constants::DETAIL);

    std::pair<double, double> unobstructed = calculateUnobstructedOrbitSegment();

    double step = (M_2_PI - (unobstructed.phi1 - unobstructed.phi2)) / Constants::DETAIL;
    for (double phi = unobstructed.first; phi < unobstructed.phi2 + M_2_PI; phi += step) {
        // Фиксить

        orbitVA[i].position = calculateOnScreenPosition(phi);
        orbit[i].color = Constants::DEFAULT_ORBIT_COLOR;
    }

    window.draw(orbit);
}

std::pair<double, double> Orbit::calculateUnobstructedOrbitSegment() const {
    
    // Вычисляем пересечение сферы радиуса kepler.sma с плоскостью орбиты

    // Компоненты вектора нормали к плоскости орбиты:
    // A = sin(kepler.inc) * sin(kepler.raan);
    // B = sin(kepler.inc) * cos(kepler.raan) * (-1);
    // C = cos(kepler.inc);

    // Далее замена:
    // b = B / A;
    // c = C / A;

    // Если все подставить, то получим:
    double b = -cot(kepler.raan)
    double c = cot(kepler.inc) / sin(kepler.raan);
    double d = kepler.sma / Constants::EARTH_RADIUS;

    // Ищем направления пересечения проекций орбиты и Земли
    double D = (d * d - 1) * (b * b + c * c - d * d + 1);

    // Если пересечений нет, то все супер
    if (D < 0) {
        return std::make_pair(0, 0);
    }

    double phi1 = arctan((b * c + sqrt(D)) / (c * c - d * d + 1));
    double phi2 = arctan((b * c - sqrt(D)) / (c * c - d * d + 1));

    // Отбираем только те, которые лежат в верхней полуплоскости
    phi1 = constrainAngle(phi1, M_PI);
    phi2 = constrainAngle(phi2, M_PI);

    // Сортируем
    if (phi1 > phi2) {
        phi1 += phi2;
        phi2 = phi1 - phi2;
        phi1 -= phi2;
    }
    
    // Don`t even ask
    double theta = (phi1 + phi2) / 2;
    for (int i = 0; i < 3; i++) {
        Vector2f pos = calculateOnScreenPosition(theta);
        double z = -(b * pos.x + c * pos.y);

        if (z < 0) {
            double start, stop;

            if (i == 0) {
                start = phi2;
                stop = phi1;
            } else if (i == 1) {
                start = phi1 + M_PI;
                stop = phi2;
            } else if (i == 2) {
                start = phi2 + M_PI;
                stop = phi1 + M_PI;
            } else {
                start = phi1;
                stop = phi2 + M_PI;
            }

            return std::make_pair(start, stop);
        }

        theta += M_PI_2;
    }


    return std::make_pair(max(phi1, phi2), min(phi1, phi2));
}

Vector Orbit::calculateFlatPosition(double phi) const {

    // Из метода calculateUnobstructedOrbitSegment()
    double b = -cot(kepler.raan)
    double c = cot(kepler.inc) / sin(kepler.raan);

    // Уравнение проекции орбиты в полярных координатах:
    // r = sma / sqrt((b * cos(phi) + c * sin(phi))^2 + 1)

    double tmp = b * cos(phi) + c * sin(phi);
    double r = kepler.sma / sqrt(tmp * tmp + 1);

    double x = r * cos(phi);
    double y = r * sin(phi);

    return Vector(x, y, 0);
}

