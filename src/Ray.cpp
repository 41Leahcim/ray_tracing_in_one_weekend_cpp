#include "Ray.hpp"

Ray::Ray(){}

Ray::Ray(const Point3& origin, const Vec3 direction)
    : orig(origin), dir(direction){}

Point3 Ray::origin() const{
    return this->orig;
}

Vec3 Ray::direction() const{
    return this->dir;
}

Point3 Ray::at(double time) const{
    return this->orig + time * this->dir;
}
