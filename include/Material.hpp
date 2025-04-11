#pragma once

#include "Color.hpp"
#include "Hittable.hpp"

class Material{
public:
    virtual ~Material() = default;

    virtual bool scatter(
        const Ray& ray_in, const HitRecord& record, Color& attenuation, Ray& scattered) const = 0;
};

class Lambertian : public Material {
private:
    const Color albedo;
public:
    inline Lambertian(const Color albedo_value) noexcept : albedo(albedo_value) {}

    inline bool scatter(
        const Ray& ray_in, const HitRecord& record, Color& attenuation, Ray& scattered) const{
        Vec3 scatter_direction = record.normal + Vec3::random_unit_vector();
        if(scatter_direction.near_zero()){
            scatter_direction = record.normal;
        }
        scattered = Ray(record.point, scatter_direction);
        attenuation = albedo;
        return true;
    }
};


class Metal : public Material {
private:
    const Color albedo;
public:
    inline Metal(const Color albedo_value) noexcept : albedo(albedo_value) {}

    inline bool scatter(
        const Ray& ray_in, const HitRecord& record, Color& attenuation, Ray& scattered) const override
        {
        const Vec3 reflected = ray_in.direction().reflect(record.normal);
        scattered = Ray(record.point, reflected);
        attenuation = albedo;
        return true;
    }
};
