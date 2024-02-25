#include "Constants.hpp"

const float Constants::PI = 3.14159265358979323846;

const float Constants::LIGHT_SPEED = 299792458;
const float Constants::EARTH_MU = 3.986E14;
const float Constants::EARTH_RADIUS = 6.371E6;
const float Constants::ATMO_HEIGHT = 100E3;

const float Constants::HORIZONTAL_RESOLUTION = 1600;
const float Constants::VERTICAL_RESOLUTION = 900;

const float Constants::EARTH_RADIUS_ON_SCREEN = 200;
const float Constants::SCALE_FACTOR = Constants::EARTH_RADIUS_ON_SCREEN / Constants::EARTH_RADIUS;
const float Constants::SATELLITE_RADIUS = 5;
const float Constants::LINE_THICKNESS = 5;
const unsigned Constants::DETAIL = 500;

const float Constants::SMA_CHANGE_RATE = 2000;
const float Constants::INC_CHANGE_RATE = 4;
const float Constants::RAAN_CHANGE_RATE = 4;
const float Constants::NUMBER_OF_SATELLITES_CHANGE_RATE = 4;

const float Constants::SIMULATION_SPEED = 1;
const float Constants::ORBIT_DECAY_SPEED = 5;

const float Constants::REQUEST_POINT_RADIUS = 4;
const float Constants::REQUEST_DURATION = 3;
const float Constants::TIME_BETWEEN_REQUESTS = 1.2;

const long long Constants::START_BALANCE = 5E8;

const long long Constants::NUMBER_OF_SATELLITES_COST = 1E5;
const long long Constants::SMA_COST = 1E5;
const long long Constants::INC_COST = 1E4;

const long long Constants::REQUEST_GAIN = 1E7;
const long long Constants::REQUEST_LOSS = 5E4;

const unsigned Constants::FRAME_RATE = 60;
const unsigned Constants::GAME_DURATION_SECONDS = 60;
const unsigned Constants::MONTH_IN_YEAR = 12;
const unsigned Constants::START_YEAR = 2023;
const unsigned Constants::START_MONTH = 5;
const unsigned Constants::END_YEAR = 2041;
const unsigned Constants::END_MONTH = 1;
const unsigned Constants::AMOUNT_OF_MONTHS = Constants::END_MONTH + Constants::MONTH_IN_YEAR * Constants::END_YEAR - Constants::START_MONTH - Constants::MONTH_IN_YEAR * Constants::START_YEAR;
const long long unsigned Constants::TIME_DISPLAY_INCREASE_RATE = Constants::FRAME_RATE * Constants::GAME_DURATION_SECONDS / Constants::AMOUNT_OF_MONTHS;
const std::string Constants::MONTH_NAMES[] = { "JAN", "FEB", "MAR", "APR", "MAY", "JUN", "JUL", "AUG", "SEP", "OCT", "NOV", "DEC" };

const long long Constants::AMOUNT_OF_MONEY_REQUIRED_TO_WIN = 1E9;

const unsigned long long Constants::STRING_TRUNCATION_LENGTH = 1E5;

const Constants::City Constants::CITIES[] = {
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
};

const sf::Color Constants::MAIN_COLOR = sf::Color(139, 229, 208, 255);
const sf::Color Constants::TUTORIAL_PLATE_COLOR = sf::Color(255, 255, 255, 200);
const sf::Color Constants::DEFAULT_ORBIT_COLOR = sf::Color::Green;
const sf::Color Constants::SELECTION_ORBIT_COLOR = sf::Color::Magenta;
const sf::Color Constants::SATELLITE_COLOR = sf::Color::Red;

const unsigned Constants::FPS_DISPLAY_FONT_SIZE = 24;
const unsigned Constants::BALANCE_DISPLAY_FONT_SIZE = 36;
const unsigned Constants::LAUNCH_PRICE_DISPLAY_FONT_SIZE = 48;

const float Constants::TEXT_OFFSET = 10.f;
const sf::Vector2f Constants::FPS_DISPLAY_POSITION = sf::Vector2f(-Constants::HORIZONTAL_RESOLUTION / 2 + Constants::TEXT_OFFSET, -Constants::VERTICAL_RESOLUTION / 2 + Constants::TEXT_OFFSET);
const sf::Vector2f Constants::BALANCE_DISPLAY_POSITION = sf::Vector2f(Constants::HORIZONTAL_RESOLUTION / 2 - Constants::TEXT_OFFSET * 2, -Constants::VERTICAL_RESOLUTION / 2 + Constants::TEXT_OFFSET);
const sf::Vector2f Constants::LAUNCH_PRICE_DISPLAY_POSITION = sf::Vector2f(0, -Constants::VERTICAL_RESOLUTION / 2 + Constants::TEXT_OFFSET * 3);
const sf::Vector2f Constants::DATE_DISPLAY_POSITION = sf::Vector2f(0, Constants::VERTICAL_RESOLUTION / 2 - Constants::TEXT_OFFSET * 5);

const sf::Vector2f Constants::TUTORIAL_PLATE_SIZE = sf::Vector2f(490.f, 340.f);
const sf::Vector2f Constants::TUTORIAL_PLATE_POSITION = sf::Vector2f(-Constants::HORIZONTAL_RESOLUTION / 2 + 50.f, Constants::VERTICAL_RESOLUTION / 2 - TUTORIAL_PLATE_SIZE.y - 50.f);

const std::string Constants::EARTH_TEXTURE_PATH = "../images/earth.png";
const std::string Constants::TUTORIAL_PLATE_TEXTURE_PATH = "../images/tutorial.png";
