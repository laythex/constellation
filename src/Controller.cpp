// end game screens
// cities rework & requests list

#include <iostream>
#include <cmath>

#include "Controller.hpp"

Controller::Controller() {
    onStart();

    sf::Clock deltaClock;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        deltaTimeSeconds = deltaClock.restart().asSeconds();

        onUpdate();

        window.display();
    }
}

void Controller::onStart() {
    window.create(sf::VideoMode(Constants::HORIZONTAL_RESOLUTION, Constants::VERTICAL_RESOLUTION), "Satellite Constellation");
    window.setFramerateLimit(Constants::FRAME_RATE);

    sf::View view(sf::Vector2f(0, 0), sf::Vector2f(Constants::HORIZONTAL_RESOLUTION, Constants::VERTICAL_RESOLUTION));
    window.setView(view);

    frameTicker = 0;

    balance = Constants::START_BALANCE;

    isGameEnded = false;
    isGameWon = false;

    isSelecting = false;

    deltaNumberOfSatellites = 1;
    timeElapsedBetweenRequests = 0;

    uiController = UIController();
    uiController.createTextBoxes();

    earthTexture.loadFromFile(Constants::EARTH_TEXTURE_PATH);

    earth = sf::CircleShape(Constants::EARTH_RADIUS_ON_SCREEN);
    earth.setTexture(&earthTexture);
    earth.setOrigin(Constants::EARTH_RADIUS_ON_SCREEN, Constants::EARTH_RADIUS_ON_SCREEN);
    earth.setPosition(0, 0);

    tutorialPlateTexture.loadFromFile(Constants::TUTORIAL_PLATE_TEXTURE_PATH);

    tutorialPlate = sf::RectangleShape(Constants::TUTORIAL_PLATE_SIZE);
    tutorialPlate.setTexture(&tutorialPlateTexture);
    tutorialPlate.setFillColor(Constants::TUTORIAL_PLATE_COLOR);
    tutorialPlate.setPosition(Constants::TUTORIAL_PLATE_POSITION);
}

void Controller::onUpdate() {
    frameTicker++;

    checkEndGameConditions();

    if (isGameEnded) {
        handleEndGame();
        return;
    }

    handleLaunchKeys();

    if (isSelecting)
        handleSelection();

    handleOrbitDecay();

    handleRequests();

    uiController.updateTextBoxes(deltaTimeSeconds, balance, launchCost, getNumberOfMonth());

    window.clear();

    window.draw(earth);
    window.draw(tutorialPlate);

    drawRequests();

    uiController.drawTextBoxes(window, isSelecting);

    mainNet.advanceTimeSecs(Constants::SIMULATION_SPEED);
    drawConstellation(mainNet, false);

    if (isSelecting) {
        selectionNet.advanceTimeSecs(Constants::SIMULATION_SPEED);
        drawConstellation(selectionNet, true);
    }
}

void Controller::drawConstellation(Constellation net, bool isSelectionNet) {
    for (auto& sat : net.sats) {
        float theta1 = -1, theta2 = -1, dtheta, theta;
        bool prev = false, curr = false;
        int dir = 0;

        Kepler kep = sat.getKepler();
        Vector pos;
        for (float theta = 0; theta < 2 * Constants::PI; theta += 2 * Constants::PI / Constants::DETAIL) {

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
}

void Controller::drawRequests() {
    for (unsigned int i = 0; i < requests.size(); i++) {
        window.draw(requests[i].startPoint);
        window.draw(requests[i].endPoint);
        window.draw(requests[i].path);
    }
}

void Controller::handleRequests() {
    timeElapsedBetweenRequests += deltaTimeSeconds;
    if (timeElapsedBetweenRequests > Constants::TIME_BETWEEN_REQUESTS) {
        Request req;
        requests.push_back(req);

        timeElapsedBetweenRequests = 0;
    }

    for (auto& request : requests) {
        request.timeToExpire -= deltaTimeSeconds;
    }

    while(requests.size() > 0) {
        if (requests[0].timeToExpire > 0) break;
        requests.erase(requests.begin());
    }

    long long gain = 0;
    for (auto& request : requests) {
        request.Connect(mainNet);
        
        if (request.isSuccessful)
            gain += Constants::REQUEST_GAIN * deltaTimeSeconds;
        else
            gain -= Constants::REQUEST_LOSS * deltaTimeSeconds;
    }

    balance += gain;
}

void Controller::handleEndGame() {
    window.clear();

    sf::Texture backgroundTexture;
    sf::RectangleShape backgroud(sf::Vector2f(Constants::HORIZONTAL_RESOLUTION, Constants::VERTICAL_RESOLUTION));
    backgroud.setOrigin(backgroud.getLocalBounds().width / 2, backgroud.getLocalBounds().height / 2);
    elonMuskAnimationFrame = 0;

    if (isGameWon) {
        elonMuskAnimationFrame = (elonMuskAnimationFrame + 1) % 6;

        sf::Texture emTexture;
        sf::RectangleShape elonmusk(sf::Vector2f(286 / 2, 712 / 2));

        backgroundTexture.loadFromFile("images/mars.png");
        backgroud.setTexture(&backgroundTexture);

        emTexture.loadFromFile("images/elonmusk" + std::to_string(elonMuskAnimationFrame) + ".png");
        elonmusk.setTexture(&emTexture);
        elonmusk.setPosition(-72, 100);

        window.draw(backgroud);
        window.draw(elonmusk);
    }
    else {
        if (balance > 0)
            backgroundTexture.loadFromFile("images/fallout.png");
        else
            backgroundTexture.loadFromFile("images/bankrupt.png");

        backgroud.setTexture(&backgroundTexture);
        window.draw(backgroud);
    }

    window.display();
}

void Controller::checkEndGameConditions() {
    if (getNumberOfMonth() > Constants::AMOUNT_OF_MONTHS || balance < 0) {
        isGameEnded = true;
        isGameWon = false;
    }

    if (balance > Constants::AMOUNT_OF_MONEY_REQUIRED_TO_WIN) {
        isGameEnded = true;
        isGameWon = true;
    }
}

void Controller::handleSelection()
{
    int numberOfSatellites = selectionNet.sats.size();

    changeSelectionOrbit();

    bool needToEvenize = numberOfSatellites != selectionNet.sats.size();
    if (needToEvenize)
        evenizeSelectionNet();

    launchCost = calculateLaunchPrice();
}

void Controller::changeSelectionOrbit() {
    float deltaSma = 0, deltaInc = 0, deltaRaan = 0;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        deltaSma += Constants::SMA_CHANGE_RATE * deltaTimeSeconds;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        deltaSma -= Constants::SMA_CHANGE_RATE * deltaTimeSeconds;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
        deltaInc += Constants::INC_CHANGE_RATE * deltaTimeSeconds;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
        deltaInc -= Constants::INC_CHANGE_RATE * deltaTimeSeconds;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        deltaRaan += Constants::RAAN_CHANGE_RATE * deltaTimeSeconds;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        deltaRaan -= Constants::RAAN_CHANGE_RATE * deltaTimeSeconds;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
        deltaNumberOfSatellites += Constants::NUMBER_OF_SATELLITES_CHANGE_RATE * deltaTimeSeconds;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
        deltaNumberOfSatellites -= Constants::NUMBER_OF_SATELLITES_CHANGE_RATE * deltaTimeSeconds;
    }

    for (auto& sat : selectionNet.sats) {
        sat.getKepler().sma += deltaSma / Constants::SCALE_FACTOR;
        if (sat.getKepler().sma < Constants::EARTH_RADIUS * 1.01)
            sat.getKepler().sma = Constants::EARTH_RADIUS * 1.01;

        sat.getKepler().inc = Tools::constrainAngle(sat.getKepler().inc + deltaInc);
        sat.getKepler().raan = Tools::constrainAngle(sat.getKepler().raan + deltaRaan);
    }

    if (deltaNumberOfSatellites < 1) deltaNumberOfSatellites = 1;
    unsigned deltaNumberOfSatellitesRounded = round(deltaNumberOfSatellites);

    if (deltaNumberOfSatellitesRounded > selectionNet.sats.size())
        while (deltaNumberOfSatellitesRounded > selectionNet.sats.size())
            selectionNet.sats.push_back(Satellite(frameTicker, selectionNet[0].getKepler()));
    else if (deltaNumberOfSatellitesRounded < selectionNet.sats.size())
        while (deltaNumberOfSatellitesRounded < selectionNet.sats.size())
            selectionNet.sats.pop_back();
}

void Controller::evenizeSelectionNet() {
    float ta0 = selectionNet.sats[0].getKepler().ta;
    float deltaTa = 2 * Constants::PI / selectionNet.sats.size();
    for (unsigned int i = 1; i < selectionNet.sats.size(); i++) {
        selectionNet.sats[i].getKepler().ta = ta0 + deltaTa * i;
    }
}

void Controller::handleLaunchKeys() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) && !isSelecting) {
        isSelecting = true;

        selectionNet.sats.push_back(Satellite(frameTicker, Kepler(Constants::EARTH_RADIUS * 1.2f, Constants::PI / 3, Constants::PI / 6, 0)));
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && isSelecting) {
        isSelecting = false;

        if (true || balance > launchCost) {
            for (auto& sat : selectionNet.sats) mainNet.sats.push_back(sat);

            balance -= launchCost;
        }
        deltaNumberOfSatellites = 1;

        selectionNet.sats.clear();
    }
}

void Controller::handleOrbitDecay() {
    for (auto& sat : mainNet.sats) {
        sat.getKepler().sma -= Constants::ORBIT_DECAY_SPEED / Constants::SCALE_FACTOR * deltaTimeSeconds;

        if (sat.getKepler().sma < Constants::EARTH_RADIUS + Constants::ATMO_HEIGHT) mainNet.sats.erase(remove(mainNet.sats.begin(), mainNet.sats.end(), sat));
    }
}

unsigned long long Controller::calculateLaunchPrice() {
    return selectionNet.sats.size() * Constants::NUMBER_OF_SATELLITES_COST +
        selectionNet[0].getKepler().sma * Constants::SMA_COST * Constants::SCALE_FACTOR +
        abs(selectionNet[0].getKepler().inc - Constants::PI) / Constants::PI * 2 * Constants::INC_COST;
}

unsigned long long Controller::getNumberOfMonth() {
    unsigned long long numberOfMonth = frameTicker / Constants::TIME_DISPLAY_INCREASE_RATE;
    return numberOfMonth;
}
