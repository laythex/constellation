#include <cmath>

#include "Vector.hpp"

Vector::Vector() : Vector(0, 0, 0) {}

Vector::Vector(float x, float y, float z) : x(x), y(y), z(z) { }

float Vector::getMagnitude() const {
    return sqrt(dot(*this));
}

Vector Vector::normalize() const {
    return (*this) / getMagnitude();
}

float Vector::dot(Vector other) const {
    return x * other.getX() + y * other.getY() + z * other.getZ();
}

Vector Vector::cross(Vector other) const {
    float xc = y * other.getZ() - z * other.getY();
    float yc = z * other.getX() - x * other.getZ();
    float zc = x * other.getY() - y * other.getX();
    return Vector(xc, yc, zc);
}

float Vector::getX() const { return x; }
float Vector::getY() const { return y; }
float Vector::getZ() const { return z; }

void Vector::setX(float _x) { x = _x; }
void Vector::setY(float _y) { y = _y; }
void Vector::setZ(float _z) { z = _z; }

bool Vector::operator==(Vector other) const {
    return x == other.getX() && y == other.getY() && z == other.getZ();
}

Vector Vector::operator+(Vector other) const {
    return Vector(x + other.getX(), y + other.getY(), z + other.getZ());
}

Vector Vector::operator-(Vector other) const {
    return Vector(x - other.getX(), y - other.getY(), z - other.getZ());
}

Vector Vector::operator*(float a) const {
    return Vector(x * a, y * a, z * a);
}

Vector Vector::operator/(float a) const {
    return Vector(x / a, y / a, z / a);
}
