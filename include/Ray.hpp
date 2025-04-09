#pragma once

#include "Vec3.hpp"

class Ray{
private:
    Point3 orig;
    Vec3 dir;
public:
    inline constexpr Ray() noexcept : orig(), dir() {}
    inline Ray(const Point3 origin, const Vec3 direction) noexcept : orig(origin), dir(direction) {}
    inline virtual ~Ray() noexcept {}

    inline constexpr const Point3& origin() const noexcept {
        return orig;
    }

    inline constexpr const Vec3& direction() const noexcept {
        return dir;
    }

    inline const Point3 at(const double time) const noexcept {
        return orig + time * dir;
    }
};
