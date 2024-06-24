#pragma once

#include <cmath>

#include "Constants.hpp"
    
class Vector {
public:
    Vector();
    Vector(double x, double y, double z);

    double getMagnitude() const;
    Vector normalize() const;

    double dot(const Vector& other) const;
    Vector cross(const Vector& other) const;

    double getX() const;
    double getY() const;
    double getZ() const;

    void setX(double _x);
    void setY(double _y);
    void setZ(double _z);

    bool operator==(const Vector& other) const;
    Vector operator+(const Vector& other) const;
    Vector operator-(const Vector& other) const;
    Vector operator*(double a) const;
    Vector operator/(double a) const;

private:
    double x, y, z;
};

std::ostream& operator<<(std::ostream& os, const Vector& v);