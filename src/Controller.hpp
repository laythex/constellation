#pragma once

#include <SFML/Graphics.hpp>

#include "Constants.hpp"
#include "Tools.hpp"
#include "Constellation.hpp"
#include "Request.hpp"
#include "Input.hpp"
#include "UIController.hpp"

class Controller {
public:
	Controller();

private:

	void onStart();
	void onUpdate();

	void handleConstellation();
	void handleRequests();
	void handleEndGame();

	sf::RenderWindow window;

	Input input;
	UIController uiController;
	Constellation constellation;

	bool isGameEnded;
	bool isGameWon;

	unsigned long long balance;

	unsigned elonMuskAnimationFrame;

	double deltaTime;
	unsigned long long frameTicker;

	double deltaNumberOfSatellites;
	double timeElapsedBetweenRequests;

	std::vector<Request> requests;

	sf::CircleShape earth;
	sf::RectangleShape tutorialPlate;

	sf::Texture earthTexture;
	sf::Texture tutorialPlateTexture;
};
