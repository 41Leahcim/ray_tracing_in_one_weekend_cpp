#pragma once

#include "Vec3.hpp"

class Ray{
public:
    Ray();
    Ray(const Point3& origin, const Vec3 direction);

    Point3 origin() const;
    Vec3 direction() const;

    Point3 at(double time) const;
private:
    Point3 orig;
    Vec3 dir;
};
