#include "Vector.hpp"

Vector::Vector() : Vector(0, 0, 0) {}

Vector::Vector(double x, double y, double z) : x(x), y(y), z(z) { }

double Vector::getMagnitude() const {
    return sqrt(dot(*this));
}

Vector Vector::normalize() const {
    return (*this) / getMagnitude();
}

double Vector::dot(const Vector& other) const {
    return x * other.getX() + y * other.getY() + z * other.getZ();
}

Vector Vector::cross(const Vector& other) const {
    double xc = y * other.getZ() - z * other.getY();
    double yc = z * other.getX() - x * other.getZ();
    double zc = x * other.getY() - y * other.getX();
    return Vector(xc, yc, zc);
}

double Vector::getX() const { return x; }
double Vector::getY() const { return y; }
double Vector::getZ() const { return z; }

void Vector::setX(double _x) { x = _x; }
void Vector::setY(double _y) { y = _y; }
void Vector::setZ(double _z) { z = _z; }

bool Vector::operator==(const Vector& other) const {
    return x == other.getX() && y == other.getY() && z == other.getZ();
}

Vector Vector::operator+(const Vector& other) const {
    return Vector(x + other.getX(), y + other.getY(), z + other.getZ());
}

Vector Vector::operator-(const Vector& other) const {
    return Vector(x - other.getX(), y - other.getY(), z - other.getZ());
}

Vector Vector::operator*(double a) const {
    return Vector(x * a, y * a, z * a);
}

Vector Vector::operator/(double a) const {
    return Vector(x / a, y / a, z / a);
}

std::ostream& operator<<(std::ostream& os, const Vector& v) {
    os << "x: " << v.getX() << '\t' << "y: " << v.getY() << '\t' << "z: " << v.getZ();
    return os;
}   