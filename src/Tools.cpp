#include <cmath>
#include <chrono>
#include <random>

#include "Tools.hpp"

int Tools::rand_uns(int min, int max) {
	unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
	static std::default_random_engine e(seed);
	std::uniform_int_distribution<int> d(min, max);
	return d(e);
}

float Tools::constrainAngle(float angle) {
    while (angle > 2 * Constants::PI)
        angle -= 2 * Constants::PI;
    while (angle < 0)
        angle += 2 * Constants::PI;
    return angle;
}

std::string Tools::formatString(long long n) {
    n = n / Constants::STRING_TRUNCATION_LENGTH * Constants::STRING_TRUNCATION_LENGTH;

    std::string s = std::to_string(n);
    std::string r = "";
    for (int i = s.size() - 1; i >= 0; i--) {
        r = s[i] + r;
        if (i != 0 && (s.size() - i) % 3 == 0) {
            r = '.' + r;
        }
    }

    return r;
}

