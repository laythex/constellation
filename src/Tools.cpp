#include "Tools.hpp"

int Tools::rand_uns(int min, int max) {
	unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
	static std::default_random_engine e(seed);
	std::uniform_int_distribution<int> d(min, max);
	return d(e);
}

double Tools::constrainAngle(double angle, double cap) {
    while (angle > cap)
        angle -= cap;
    while (angle < 0)
        angle += cap;
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

sf::Vector2f Tools::convertWorldToScreen(Vector worldPosition) {

    // Переводим в нужную систему координат
    double x = worldPosition.getX() * Constants::SCALE_FACTOR;
    double y = worldPosition.getY() * Constants::SCALE_FACTOR * (-1);

    // Кастуем в флоаты и возвращаем
    return sf::Vector2f(static_cast<float>(x), static_cast<float>(y));
}
