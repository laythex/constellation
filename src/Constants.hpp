#pragma once

#include <limits>

#include <SFML/Graphics.hpp>

class Constants {
public:
	static const float PI;

	static const float LIGHT_SPEED;
	static const float EARTH_MU;
	static const float EARTH_RADIUS;
	static const float ATMO_HEIGHT;

	static const float HORIZONTAL_RESOLUTION;
	static const float VERTICAL_RESOLUTION;

	static const float EARTH_RADIUS_ON_SCREEN;
	static const float SCALE_FACTOR;
	static const float SATELLITE_RADIUS;
	static const float LINE_THICKNESS;
	static const unsigned DETAIL;

	static const float SMA_CHANGE_RATE;
	static const float INC_CHANGE_RATE;
	static const float RAAN_CHANGE_RATE;
	static const float NUMBER_OF_SATELLITES_CHANGE_RATE;

	static const float SIMULATION_SPEED;
	static const float ORBIT_DECAY_SPEED;

	static const float REQUEST_POINT_RADIUS;
	static const float REQUEST_DURATION;
	static const float TIME_BETWEEN_REQUESTS;

	static const long long START_BALANCE;

	static const long long NUMBER_OF_SATELLITES_COST;
	static const long long SMA_COST;
	static const long long INC_COST;

	static const long long REQUEST_GAIN;
	static const long long REQUEST_LOSS;

	static const unsigned FRAME_RATE;
	static const unsigned GAME_DURATION_SECONDS;
	static const unsigned MONTH_IN_YEAR;
	static const unsigned START_YEAR;
	static const unsigned START_MONTH;
	static const unsigned END_YEAR;
	static const unsigned END_MONTH;
	static const unsigned AMOUNT_OF_MONTHS;
	static const unsigned long long TIME_DISPLAY_INCREASE_RATE;
	static const std::string MONTH_NAMES[12];

	static const long long AMOUNT_OF_MONEY_REQUIRED_TO_WIN;

	static const unsigned long long STRING_TRUNCATION_LENGTH;

	struct City {
		std::string name;
		float lat, lon;
		long long population;
	};

	static const City CITIES[14];

	static const sf::Color MAIN_COLOR;
	static const sf::Color TUTORIAL_PLATE_COLOR;
	static const sf::Color DEFAULT_ORBIT_COLOR;
	static const sf::Color SELECTION_ORBIT_COLOR;
	static const sf::Color SATELLITE_COLOR;
	
	static const unsigned FPS_DISPLAY_FONT_SIZE;
	static const unsigned BALANCE_DISPLAY_FONT_SIZE;
	static const unsigned LAUNCH_PRICE_DISPLAY_FONT_SIZE;

	static const float TEXT_OFFSET;
	static const sf::Vector2f FPS_DISPLAY_POSITION;
	static const sf::Vector2f BALANCE_DISPLAY_POSITION;
	static const sf::Vector2f LAUNCH_PRICE_DISPLAY_POSITION;
	static const sf::Vector2f DATE_DISPLAY_POSITION;

	static const sf::Vector2f TUTORIAL_PLATE_SIZE;
	static const sf::Vector2f TUTORIAL_PLATE_POSITION;

	static const std::string EARTH_TEXTURE_PATH;
	static const std::string TUTORIAL_PLATE_TEXTURE_PATH;
};
