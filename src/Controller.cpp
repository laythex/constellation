#include "Controller.hpp"

#include <iostream>
// end game screens
// cities rework & requests list

Controller::Controller() : constellation(Constellation()) {
    
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

        deltaTime = deltaClock.restart().asSeconds();

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

    deltaNumberOfSatellites = 1;
    timeElapsedBetweenRequests = 0;

    input = Input();

    uiController = UIController();
    uiController.createTextBoxes();

    earthTexture.loadFromFile(Constants::EARTH_TEXTURE_PATH);

    earth = sf::CircleShape(Constants::EARTH_RADIUS_ON_SCREEN);
    earth.setTexture(&earthTexture);
    earth.setOrigin(Constants::EARTH_RADIUS_ON_SCREEN, Constants::EARTH_RADIUS_ON_SCREEN);
    earth.setPosition(0, 0);

    /*
    tutorialPlateTexture.loadFromFile(Constants::TUTORIAL_PLATE_TEXTURE_PATH);

    tutorialPlate = sf::RectangleShape(Constants::TUTORIAL_PLATE_SIZE);
    tutorialPlate.setTexture(&tutorialPlateTexture);
    tutorialPlate.setFillColor(Constants::COLOR_TUTORIAL_PLATE);
    tutorialPlate.setPosition(Constants::TUTORIAL_PLATE_POSITION);
    */
}

void Controller::onUpdate() {
    frameTicker++;

    input.updateInput(deltaTime);

    // checkEndGameConditions();

    // if (isGameEnded) {
    //     handleEndGame();
    //     return;
    // }

    handleConstellation();

    // handleRequests();

    // uiController.updateTextBoxes(deltaTime, balance, constellation.getLaunchPrice(), getNumberOfMonth());

    window.clear();

    window.draw(earth);
    window.draw(tutorialPlate);

    // drawRequests();

    // uiController.drawTextBoxes(window, isSelecting);
    constellation.draw(window);
}

void Controller::handleConstellation() {
    constellation.advanceTime(deltaTime);
    constellation.decayOrbits(deltaTime);

    Kepler delta(input.getDeltaSma(), input.getDeltaInc(), input.getDeltaRaan());
    constellation.updateSelectionOrbit(delta, input.getDeltaSatCount());

    bool hasLaunched = constellation.handleLaunchKeys(input.isSelectKeyPressed(), input.isLaunchKeyPressed(), balance);
    if (hasLaunched) {
        balance -= constellation.getLaunchPrice();
    }
}

/*
void Controller::drawRequests() {
    for (unsigned int i = 0; i < requests.size(); i++) {
        window.draw(requests[i].startPoint);
        window.draw(requests[i].endPoint);
        window.draw(requests[i].path);
    }
}
*/

void Controller::handleRequests() {
    timeElapsedBetweenRequests += deltaTime;
    if (timeElapsedBetweenRequests > Constants::TIME_BETWEEN_REQUESTS) {
        Request req;
        requests.push_back(req);

        timeElapsedBetweenRequests = 0;
    }

    for (auto& request : requests) {
        request.timeToExpire -= deltaTime;
    }

    while(requests.size() > 0) {
        if (requests[0].timeToExpire > 0) break;
        requests.erase(requests.begin());
    }

    long long gain = 0;
    for (auto& request : requests) {
        request.Connect(constellation);
        
        if (request.isSuccessful)
            gain += Constants::REQUEST_GAIN * deltaTime;
        else
            gain -= Constants::REQUEST_LOSS * deltaTime;
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
            backgroundTexture.loadFromFile("../images/fallout.png");
        else
            backgroundTexture.loadFromFile("../images/bankrupt.png");

        backgroud.setTexture(&backgroundTexture);
        window.draw(backgroud);
    }

    window.display();
}

/*
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
*/

/*
unsigned long long Controller::getNumberOfMonth() {
    return numberOfMonth = frameTicker / Constants::TIME_DISPLAY_INCREASE_RATE;
}
*/
