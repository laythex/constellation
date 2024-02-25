#pragma once

#include "Constants.hpp"
    
class Vector {
public:
    Vector();
    Vector(float x, float y, float z);

    float getMagnitude() const;
    Vector normalize() const;

    float dot(Vector other) const;
    Vector cross(Vector other) const;

    float getX() const;
    float getY() const;
    float getZ() const;

    void setX(float _x);
    void setY(float _y);
    void setZ(float _z);

    bool operator==(Vector other) const;
    Vector operator+(Vector other) const;
    Vector operator-(Vector other) const;
    Vector operator*(float a) const;
    Vector operator/(float a) const;

private:
    float x, y, z;
};
