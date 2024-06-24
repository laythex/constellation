#include "SelectionOrbit.hpp"

SelectionOrbit::SelectionOrbit() : Orbit(Kepler(Constants::SMA_DEFAULT,
                                                Constants::INC_DEFAULT,
                                                Constants::RAAN_DEFAULT)) { }

void SelectionOrbit::changeKepler(Kepler delta) {
    kepler.sma += delta.sma;
    if (kepler.sma < Constants::EARTH_RADIUS * 1.01) {
        kepler.sma = Constants::EARTH_RADIUS * 1.01;
    }

    kepler.inc = Tools::constrainAngle(kepler.inc + delta.inc);
    kepler.raan = Tools::constrainAngle(kepler.raan + delta.raan);
}


void SelectionOrbit::addSatellite() {
    // Сделать
}

void SelectionOrbit::removeSatellite() { 
    // Сделать
}

void SelectionOrbit::changeSatCount(int deltaSatCount) {

    // Сделать
    
    /*
    if (deltaSatCount < 1) deltaSatCount = 1;
    unsigned deltaSatCountRounded = round(deltaSatCount);

    if (deltaSatCountRounded > selectionNet.sats.size())
        while (deltaSatCountRounded > selectionNet.sats.size())
            selectionNet.sats.push_back(Satellite(frameTicker, selectionNet[0].getKepler()));
    else if (deltaSatCountRounded < selectionNet.sats.size())
        while (deltaSatCountRounded < selectionNet.sats.size())
            selectionNet.sats.pop_back();

    void Controller::evenizeSelectionNet() {
    double ta0 = selectionNet.sats[0].getKepler().ta;
    double deltaTa = 2 * Constants::PI / selectionNet.sats.size();
    for (unsigned int i = 1; i < selectionNet.sats.size(); i++) {
        selectionNet.sats[i].getKepler().ta = ta0 + deltaTa * i;
    }
}
    */
}

void SelectionOrbit::reset() {
    kepler = Kepler(Constants::SMA_DEFAULT, Constants::INC_DEFAULT, Constants::RAAN_DEFAULT);
}

unsigned long long SelectionOrbit::calculateLaunchPrice() const {
    return satellites.size() * Constants::NUMBER_OF_SATELLITES_COST +
        kepler.sma * Constants::SMA_COST * Constants::SCALE_FACTOR +
        fabs(kepler.inc - M_PI) / M_PI_2 * Constants::INC_COST;
}
