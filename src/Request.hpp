#pragma once

#include <SFML/Graphics.hpp>

#include "Constants.hpp"
#include "Tools.hpp"
#include "Constellation.hpp"

using std::size;

class Request
{
public:
	Request();

	void Connect(Constellation net);

	sf::VertexArray path;
	sf::CircleShape startPoint, endPoint;

	bool isSuccessful;
	double timeToExpire;

private:
	void generateCities();
	void generatePoints();

	Constants::City startCity, endCity;
	double lat1, lon1, lat2, lon2;
};
