#pragma once

#include "Hittable.hpp"
#include "Vec3.hpp"

class Sphere : public Hittable {
private:
    const Point3 center;
    const double radius;
public:
    inline Sphere(const Point3 center_point, const double rad) noexcept : center(center_point), radius(std::fmax(0, rad)) {}

    inline bool hit(const Ray& ray, const double ray_time_min, const double ray_time_max, HitRecord& record) const override {
        const Vec3 origin_center = center - ray.origin();
        const double a = ray.direction().length_squared();
        const double h = ray.direction().dot(origin_center);
        const double c = origin_center.length_squared() - radius * radius;

        const double discriminant = h * h - a * c;
        if(discriminant < 0){
            return false;
        }

        const double sqrt_discriminant = std::sqrt(discriminant);

        // Find the nearest root that lies in the acceptable range.
        double root = (h - sqrt_discriminant) / a;
        if(root <= ray_time_min || root >= ray_time_max){
            root = (h + sqrt_discriminant) / a;
            if(root <= ray_time_min || root >= ray_time_max){
                return false;
            }
        }

        const Point3 point = ray.at(root);
        record = HitRecord{
            .point = point,
            .normal = (point - center) / radius,
            .time = root,
        };
        const Vec3 outward_normal = (record.point - center) / radius;
        record.set_face_normal(ray, outward_normal);

        return true;
    }
};
