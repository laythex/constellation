#include "Orbit.hpp"
#include <iostream>
Orbit::Orbit(Kepler kepler) : kepler(kepler), isDecayed(false) { }

void Orbit::setKepler(Kepler newKepler) {
    kepler = newKepler;
}

Kepler Orbit::getKepler() const {
    return kepler;
}

void Orbit::setSatellites(std::vector<std::pair<Satellite, double>> sats) {
    satellites = sats;
}

std::vector<std::pair<Satellite, double>> Orbit::getSatellites() const {
    return satellites;
}

bool Orbit::getIsDecayed() const {
    return isDecayed;
}

void Orbit::advanceTime(double deltaTime) {
    double T = kepler.calculateOrbitalPeriod();
    double deltaTa = M_2_PI * deltaTime / T * Constants::SIMULATION_SPEED;

    // Увеличиваем истинную аномалию
    for (std::pair<Satellite, double>& satellite : satellites) {
        satellite.second = Tools::constrainAngle(satellite.second + deltaTa);
    }
}

void Orbit::decay(double deltaTime) {
    kepler.sma -= Constants::ORBIT_DECAY_SPEED * deltaTime;

    if (kepler.sma < Constants::EARTH_RADIUS + Constants::ATMO_HEIGHT) {
        isDecayed = true;
    }
}

void Orbit::draw(sf::RenderWindow& window) const { 
    std::cout << "Drawing orbit" << std::endl;
    sf::VertexArray orbitVA(sf::LineStrip, Constants::ORBIT_DETAILING);

    // Углы, между которыми зажата видидимая часть орбиты
    std::pair<double, double> unobstructed = calculateUnobstructedOrbitSegment();
    double phi1 = unobstructed.first, phi2 = unobstructed.second;

    // Шагаем по видимой части орбиты
    double step = (M_2_PI - (phi1 - phi2)) / Constants::ORBIT_DETAILING;
    for (unsigned i = 0; i < Constants::ORBIT_DETAILING; i++) {
        // Координата текущего узла
        double phi = phi1 + step * i;
        Vector flatPosition = calculateFlatPosition(phi);

        // Фиксить
        orbitVA[i].position = Tools::convertWorldToScreen(flatPosition);
        orbitVA[i].color = Constants::COLOR_ORBIT;
    }

    window.draw(orbitVA);

    sf::CircleShape shape(50);
    window.draw(shape);
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
    double b = cos(kepler.raan) / sin(kepler.raan) * (-1);
    double c = cos(kepler.inc) / sin(kepler.inc) / sin(kepler.raan);
    double d = kepler.sma / Constants::EARTH_RADIUS;

    // Ищем направления пересечения проекций орбиты и Земли
    double D = (d * d - 1) * (b * b + c * c - d * d + 1);

    // Если пересечений нет, то все супер
    if (D < 0) {
        return std::make_pair(0, 0);
    }

    double phi1 = atan((b * c + sqrt(D)) / (c * c - d * d + 1));
    double phi2 = atan((b * c - sqrt(D)) / (c * c - d * d + 1));

    // Отбираем только те, которые лежат в верхней полуплоскости
    phi1 = Tools::constrainAngle(phi1, M_PI);
    phi2 = Tools::constrainAngle(phi2, M_PI);

    // Сортируем
    if (phi1 > phi2) {
        phi1 += phi2;
        phi2 = phi1 - phi2;
        phi1 -= phi2;
    }
    
    // Ищем сегмент орбиты, который закрыт Землей
    double theta = (phi1 + phi2) / 2;
    for (int i = 0; i < 3; i++) {
        Vector pos = calculateFlatPosition(theta);
        double z = -(b * pos.getX() + c * pos.getY());

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

    // If my math is correct, сюда он дойти не должен
    return std::make_pair(0, 0);
}

Vector Orbit::calculateFlatPosition(double phi) const {

    // Из метода calculateUnobstructedOrbitSegment() [надо убрать повторяющийся код]
    double b = cos(kepler.raan) / sin(kepler.raan) * (-1);
    double c = cos(kepler.inc) / sin(kepler.inc) / sin(kepler.raan);

    std::cout << phi << '\t' << b << '\t' << c << std::endl;

    // Уравнение проекции орбиты в полярных координатах:
    // r = sma / sqrt((b * cos(phi) + c * sin(phi))^2 + 1)

    double tmp = b * cos(phi) + c * sin(phi);
    double r = kepler.sma / sqrt(tmp * tmp + 1);

    double x = r * cos(phi);
    double y = r * sin(phi);

    return Vector(x, y, 0);
}

