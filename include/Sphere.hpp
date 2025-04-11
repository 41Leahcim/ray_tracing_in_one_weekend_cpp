#pragma once

#include <memory>

#include "Hittable.hpp"
#include "Vec3.hpp"

class Sphere : public Hittable {
private:
    const Point3 center;
    const double radius;
    const std::shared_ptr<Material> material;
public:
    inline Sphere(const Point3 center_point, const double rad, const std::shared_ptr<Material> mat)
        : center(center_point), radius(std::fmax(0, rad)), material(mat) {}

    inline bool hit(const Ray& ray, const Interval ray_time, HitRecord& record) const override {
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
        if(!ray_time.surrounds(root)){
            root = (h + sqrt_discriminant) / a;
            if(!ray_time.surrounds(root)){
                return false;
            }
        }

        const Point3 point = ray.at(root);
        record = HitRecord{
            .point = point,
            .normal = (point - center) / radius,
            .time = root,
            .material = material
        };
        const Vec3 outward_normal = (record.point - center) / radius;
        record.set_face_normal(ray, outward_normal);

        return true;
    }
};
