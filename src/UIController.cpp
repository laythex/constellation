#include "UIController.hpp"

UIController::UIController() {
    QoreFont.loadFromFile("../fonts/Qore.ttf");
}

void UIController::createTextBoxes() {
    FPSDisplay.setFont(QoreFont);
    FPSDisplay.setCharacterSize(Constants::FPS_DISPLAY_FONT_SIZE);
    FPSDisplay.setFillColor(sf::Color::White);


    balanceDisplay.setFont(QoreFont);
    balanceDisplay.setCharacterSize(Constants::BALANCE_DISPLAY_FONT_SIZE);
    balanceDisplay.setFillColor(Constants::MAIN_COLOR);


    launchPriceDisplay.setFont(QoreFont);
    launchPriceDisplay.setCharacterSize(Constants::LAUNCH_PRICE_DISPLAY_FONT_SIZE);
    launchPriceDisplay.setFillColor(Constants::MAIN_COLOR);

    dateDisplay.setFont(QoreFont);
    dateDisplay.setCharacterSize(36);
    dateDisplay.setFillColor(Constants::MAIN_COLOR);
}

void UIController::updateTextBoxes(double deltaTimeSeconds, long long balance, unsigned long long launchPrice, unsigned long long numberOfMonth) {
    FPSDisplay.setString(std::to_string((int)(1 / deltaTimeSeconds)));
    centerText(FPSDisplay, "LU");
    FPSDisplay.setPosition(Constants::FPS_DISPLAY_POSITION);

    balanceDisplay.setString("$" + Tools::formatString(balance));
    centerText(balanceDisplay, "RU");
    balanceDisplay.setPosition(Constants::BALANCE_DISPLAY_POSITION);

    launchPriceDisplay.setString("$" + Tools::formatString(launchPrice));
    centerText(launchPriceDisplay, "CU");
    launchPriceDisplay.setPosition(Constants::LAUNCH_PRICE_DISPLAY_POSITION);

    dateDisplay.setString(getMonthAndYear(numberOfMonth));
    centerText(dateDisplay, "CD");
    dateDisplay.setPosition(Constants::DATE_DISPLAY_POSITION);
}

void UIController::drawTextBoxes(sf::RenderWindow& window, bool isSelecting) {
    window.draw(FPSDisplay);
    window.draw(balanceDisplay);
    if (isSelecting) window.draw(launchPriceDisplay);
    window.draw(dateDisplay);
}

std::string UIController::getMonthAndYear(unsigned long long numberOfMonth) {

    unsigned month = (numberOfMonth + Constants::START_MONTH) % Constants::MONTH_IN_YEAR;
    unsigned year = (numberOfMonth + Constants::START_MONTH) / Constants::MONTH_IN_YEAR + Constants::START_YEAR;

    return Constants::MONTH_NAMES[month] + ", " + std::to_string(year);
}

void UIController::centerText(sf::Text& text, std::string alignment) {
    sf::Vector2f center;

    switch (alignment[0]) {
    case 'L':
        center.x = 0;
        break;
    case 'C':
        center.x = text.getLocalBounds().width / 2;
        break;
    case 'R':
        center.x = text.getLocalBounds().width;
        break;
    }

    switch (alignment[1]) {
    case 'U':
        center.y = 0;
        break;
    case 'C':
        center.y = text.getLocalBounds().height / 2;
        break;
    case 'D':
        center.y = text.getLocalBounds().height;
        break;
    }
 
    text.setOrigin(center);
}
