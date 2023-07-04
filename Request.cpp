#pragma once

#include "Request.hpp"

#include<iostream>
using namespace std;

Request::Request() {
	timeToExpire = Constants::REQUEST_DURATION;

	generateCities();
	generatePoints();
}

void Request::Connect(Constellation net) {
	vector<Vector> route = net.sendRequest(lat1, lon1, lat2, lon2);
	isSuccessful = route.size() > 2;

	if (!isSuccessful) return;

	path = sf::VertexArray(sf::LineStrip, route.size());
	for (unsigned int i = 0; i < route.size(); i++) {
		path[i].position = sf::Vector2f(route[i].getX() * Constants::SCALE_FACTOR,  - route[i].getZ() * Constants::SCALE_FACTOR);
		path[i].color = sf::Color::Green;
	}
}

void Request::generateCities() {
	int numberOfCities = size(Constants::CITIES);
	startCity = Constants::CITIES[Tools::rand_uns(0, numberOfCities - 1)];
	endCity = Constants::CITIES[Tools::rand_uns(0, numberOfCities - 1)];

	lat1 = startCity.lat * Constants::PI / 180;
	lon1 = startCity.lon * Constants::PI / 180;
	lat2 = endCity.lat * Constants::PI / 180;
	lon2 = endCity.lon * Constants::PI / 180;
}

void Request::generatePoints() {
	startPoint = sf::CircleShape(Constants::REQUEST_POINT_RADIUS);
	endPoint = sf::CircleShape(Constants::REQUEST_POINT_RADIUS);
	startPoint.setOrigin(Constants::REQUEST_POINT_RADIUS, Constants::REQUEST_POINT_RADIUS);
	endPoint.setOrigin(Constants::REQUEST_POINT_RADIUS, Constants::REQUEST_POINT_RADIUS);
	startPoint.setFillColor(sf::Color::Cyan);
	endPoint.setFillColor(sf::Color::Cyan);

	startPoint.setPosition(-Constants::EARTH_RADIUS_ON_SCREEN * cos(lat1) * cos(lon1), -Constants::EARTH_RADIUS_ON_SCREEN * sin(lat1));
	endPoint.setPosition(-Constants::EARTH_RADIUS_ON_SCREEN * cos(lat2) * cos(lon2), -Constants::EARTH_RADIUS_ON_SCREEN * sin(lat2));
}
