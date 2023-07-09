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
	void drawConstellation(Constellation net, bool isSelectionNet);
	void drawRequests();

	void onStart();
	void onUpdate();
	void handleEndGame();
	void checkEndGameConditions();
	void handleSelection();
	void changeSelectionOrbit();
	void evenizeSelectionNet();
	void handleLaunchKeys();
	void handleRequests();
	void handleOrbitDecay();
	unsigned long long calculateLaunchPrice();
	unsigned long long getNumberOfMonth();


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
	float timeElapsedBetweenRequests;

	std::vector<Request> requests;

	sf::CircleShape earth;
	sf::RectangleShape tutorialPlate;

	sf::Texture earthTexture;
	sf::Texture tutorialPlateTexture;
};
