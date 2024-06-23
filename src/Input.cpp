#include "Input.hpp"

void Input::updateInput(double deltaTime) {
    deltaSma = 0; 
    deltaInc = 0; 
    deltaRaan = 0;
    deltaSatCount = 0;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        deltaSma += Constants::SMA_CHANGE_RATE * deltaTime;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        deltaSma -= Constants::SMA_CHANGE_RATE * deltaTime;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
        deltaInc += Constants::INC_CHANGE_RATE * deltaTime;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
        deltaInc -= Constants::INC_CHANGE_RATE * deltaTime;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        deltaRaan += Constants::RAAN_CHANGE_RATE * deltaTime;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        deltaRaan -= Constants::RAAN_CHANGE_RATE * deltaTime;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
        deltaSatCount += Constants::SAT_COUNT_CHANGE_RATE * deltaTime;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
        deltaSatCount -= Constants::SAT_COUNT_CHANGE_RATE * deltaTime;
    }

    selectKey = sf::Keyboard::isKeyPressed(sf::Keyboard::R);
    launchKey = sf::Keyboard::isKeyPressed(sf::Keyboard::Space)
}

double Input::getDeltaSma() const { 
    return deltaSma; 
}

double Input::getDeltaInc() const { 
    return deltaInc; 
}

double Input::getDeltaRaan() const { 
    return deltaRaan; 
}

int Input::getDeltaSatCount() const { 
    return deltaSatCount; 
}

bool isSelectKeyPressed() const {
    return selectKey;
}

bool isLaunchKeyPressed() const {
    return launchKey;
}
