#pragma once

#include <SFML/Graphics.hpp>

#include "Constants.hpp"
#include "Tools.hpp"

class UIController {
public:
	UIController();
	void createTextBoxes();
	void updateTextBoxes(double deltaTimeSeconds, long long balance, unsigned long long launchPrice, unsigned long long numberOfMonth);
	void drawTextBoxes(sf::RenderWindow& window, bool isSelecting);

private:
	std::string getMonthAndYear(unsigned long long numberOfMonth);
	void centerText(sf::Text& text, std::string alignment = "CC");

	sf::Font QoreFont;

	sf::Text FPSDisplay;
	sf::Text balanceDisplay;
	sf::Text launchPriceDisplay;
	sf::Text dateDisplay;
};

