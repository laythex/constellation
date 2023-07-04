#pragma once

#include <SFML/Graphics.hpp>

#include "Constants.hpp"
#include "Tools.hpp"
#include "Constellation.hpp"
#include "Request.hpp"

class Controller {
public:
	Controller();

private:
	void update();
	void drawConstellation(Constellation net, sf::Color color = sf::Color::Green);
	void drawRequests(std::vector<Request> requests);

	void onStart();
	void onUpdate();
	void handleEndGame();
	void handleSelection();
	void handleDisplayText();
	void changeSelectionOrbit();
	void evenizeSelectionNet();
	unsigned long long calculateLaunchCost();
	unsigned long long getNumberOfMonth();

	long long manageRequests(std::vector<Request>& requests, float dt);

	Constellation mainNet;
	sf::RenderWindow window;

	bool isGameEnded;
	bool isGameWon;

	long long balance;
	unsigned long long launchCost;

	unsigned elonMuskAnimationFrame;

	float deltaTimeSeconds;
	unsigned long long frameTicker;

	bool isSelecting;
    Constellation selectionNet;

	float deltaNumberOfSatellites;
};
