#pragma once

#include "Constants.hpp"

class Input {
    public:

    void updateInput(double deltaTime);

    double getDeltaSma() const;
    double getDeltaInc() const;
    double getDeltaRaan() const;
    int getDeltaSatCount() const;
    bool isSelectKeyPressed() const;
    bool isLaunchKeyPressed() const;

    private:

    double deltaSma;
    double deltaInc;
    double deltaRaan;
    int deltaSatCount;

    bool selectKey;
    bool launchKey;
};