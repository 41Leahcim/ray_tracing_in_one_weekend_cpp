#pragma once

#include "Ray.hpp"
#include "Interval.hpp"

struct HitRecord{
    Point3 point;
    Vec3 normal;
    double time;
    bool front_face;

    inline void set_face_normal(const Ray& ray, const Vec3& outward_normal) noexcept {
        // Sets the hit record normal vector.
        // NOTE: the parameter `outward_normal` is assumed to have unit length.
        front_face = ray.direction().dot(outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

class Hittable{
public:
    virtual ~Hittable() noexcept = default;
    inline virtual bool hit(const Ray& ray, const Interval ray_time, HitRecord& record) const = 0;
};
