#pragma once

#include "Constants.hpp"

#include <cmath>
#include <string>
#include <array>
#include <SFML/Graphics.hpp>

namespace Constants {

	constexpr double LIGHT_SPEED							= 299792458;
	constexpr double EARTH_MU								= 3.986E14;
	constexpr double EARTH_RADIUS							= 6.371E6;
	constexpr double ATMO_HEIGHT							= 100E3;

	constexpr double HORIZONTAL_RESOLUTION					= 960;
	constexpr double VERTICAL_RESOLUTION					= 720;

	constexpr double EARTH_RADIUS_ON_SCREEN					= 200;
	constexpr double SCALE_FACTOR							= EARTH_RADIUS_ON_SCREEN / EARTH_RADIUS;
	constexpr double SATELLITE_RADIUS						= 5;
	constexpr double LINE_THICKNESS							= 5;
	constexpr unsigned ORBIT_DETAILING						= 500;

	constexpr double SMA_CHANGE_RATE						= 2000;
	constexpr double INC_CHANGE_RATE						= 4;
	constexpr double RAAN_CHANGE_RATE						= 4;
	constexpr double SAT_COUNT_CHANGE_RATE					= 4;

	constexpr double SMA_DEFAULT							= EARTH_RADIUS * 1.5;
	constexpr double INC_DEFAULT							= M_PI / 6;
	constexpr double RAAN_DEFAULT							= M_PI / 3;

	constexpr double SIMULATION_SPEED						= 1;
	constexpr double ORBIT_DECAY_SPEED						= 5;

	constexpr double REQUEST_POINT_RADIUS					= 4;
	constexpr double REQUEST_DURATION						= 3;
	constexpr double TIME_BETWEEN_REQUESTS					= 1.2;

	constexpr long long START_BALANCE						= 5E8;

	constexpr long long NUMBER_OF_SATELLITES_COST			= 1E5;
	constexpr long long SMA_COST							= 1E5;
	constexpr long long INC_COST							= 1E4;

	constexpr long long REQUEST_GAIN						= 1E7;
	constexpr long long REQUEST_LOSS						= 5E4;

	constexpr unsigned FRAME_RATE							= 60;
	constexpr unsigned GAME_DURATION_SECONDS				= 60;
	constexpr unsigned MONTH_IN_YEAR						= 12;
	constexpr unsigned START_YEAR							= 2024;
	constexpr unsigned START_MONTH							= 5;
	constexpr unsigned END_YEAR								= 2041;
	constexpr unsigned END_MONTH							= 1;
	constexpr unsigned AMOUNT_OF_MONTHS						= END_MONTH + MONTH_IN_YEAR * END_YEAR - START_MONTH - MONTH_IN_YEAR * START_YEAR;
	constexpr long long unsigned TIME_DISPLAY_INCREASE_RATE	= FRAME_RATE * GAME_DURATION_SECONDS / AMOUNT_OF_MONTHS;
	const std::array<std::string, 12> MONTH_NAMES			= { "JAN", "FEB", "MAR", "APR", "MAY", "JUN", "JUL", "AUG", "SEP", "OCT", "NOV", "DEC" };

	constexpr long long AMOUNT_OF_MONEY_REQUIRED_TO_WIN		= 1E9;

	constexpr unsigned long long STRING_TRUNCATION_LENGTH	= 1E5;

	struct City {
		std::string name;
		float lat, lon;
		long long population;
	};

	const std::array<City, 14> CITIES = {{	// уэээ
		{"Tokyo", 3.69, 159.69, 37732000},
		{"Delhi", 28.61, 77.23, 32226000},
		{"Mumbai", 19.0761, 72.8775, 24973000},
		{"Seoul", 37.56, 126.99, 23016000},
		{"Cairo", 30.0444, 31.2358, 20296000},
		{"Beijing", 39.904, 116.4075, 18522000},
		{"Moscow", 23.76, 57.62, 17332000},
		{"Paris", 16.86, 22.35, 11060000},
		{"Johannesburg", -58.2, 48.05, 8000000},
		{"Hong Kong", -9.7, 134.2, 7450000},
		{"Saint Petersburg", 27.95, 50.32, 5384342},
		{"Sydney", -65.87, 171.21, 4840600},
		{"Barcelona", 9.38, 22.18, 4800000},
		{"Kabul", 2.53, 89.18, 4273156},
	}};

	const sf::Color COLOR_MAIN								= sf::Color(139, 229, 208, 255);
	const sf::Color COLOR_TUTORIAL_PLATE					= sf::Color(255, 255, 255, 200);
	const sf::Color COLOR_ORBIT								= sf::Color::Green;
	const sf::Color COLOR_SELECTION_ORBIT					= sf::Color::Magenta;
	const sf::Color COLOR_SATELLITE							= sf::Color::Red;

	constexpr unsigned FPS_DISPLAY_FONT_SIZE				= 24;
	constexpr unsigned BALANCE_DISPLAY_FONT_SIZE			= 36;
	constexpr unsigned LAUNCH_PRICE_DISPLAY_FONT_SIZE		= 48;

	constexpr double TEXT_OFFSET							= 10;
	const sf::Vector2f FPS_DISPLAY_POSITION					= sf::Vector2f(-HORIZONTAL_RESOLUTION / 2 + TEXT_OFFSET, -VERTICAL_RESOLUTION / 2 + TEXT_OFFSET);
	const sf::Vector2f BALANCE_DISPLAY_POSITION				= sf::Vector2f(HORIZONTAL_RESOLUTION / 2 - TEXT_OFFSET * 2, -VERTICAL_RESOLUTION / 2 + TEXT_OFFSET);
	const sf::Vector2f LAUNCH_PRICE_DISPLAY_POSITION		= sf::Vector2f(0, -VERTICAL_RESOLUTION / 2 + TEXT_OFFSET * 3);
	const sf::Vector2f DATE_DISPLAY_POSITION				= sf::Vector2f(0, VERTICAL_RESOLUTION / 2 - TEXT_OFFSET * 5);

	const sf::Vector2f TUTORIAL_PLATE_SIZE					= sf::Vector2f(490.f, 340.f);
	const sf::Vector2f TUTORIAL_PLATE_POSITION				= sf::Vector2f(-HORIZONTAL_RESOLUTION / 2 + 50.f, VERTICAL_RESOLUTION / 2 - TUTORIAL_PLATE_SIZE.y - 50.f);

	const std::string EARTH_TEXTURE_PATH					= "../images/earth.png";
	const std::string TUTORIAL_PLATE_TEXTURE_PATH			= "../images/tutorial.png";

}
