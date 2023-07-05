#pragma once

#include <SFML/Graphics.hpp>

#include "Constants.hpp"
#include "Tools.hpp"
#include "Constellation.hpp"
#include "Request.hpp"
#include "UIController.hpp"

class Controller {
public:
	Controller();

private:
	void update();
	void drawConstellation(Constellation net, bool isSelectionNet);
	void drawRequests(std::vector<Request> requests);

	void onStart();
	void onUpdate();
	void handleEndGame();
	void handleSelection();
	void changeSelectionOrbit();
	void evenizeSelectionNet();
	unsigned long long calculateLaunchCost();
	unsigned long long getNumberOfMonth();

	long long manageRequests(std::vector<Request>& requests, float dt);

	Constellation mainNet;
	sf::RenderWindow window;

	UIController uiController;

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
