#pragma once

#include <cmath>
#include <chrono>
#include <random>
#include <SFML/Graphics.hpp>

#include "Constants.hpp"
#include "Vector.hpp"

namespace Tools {
	int rand_uns(int min, int max);
	
	double constrainAngle(double angle, double cap = M_2PI);

	std::string formatString(long long n);

	// Конвертируем вектор из физической системы координат в систему координат экрана
	sf::Vector2f convertWorldToScreen(Vector worldPosition);
};

