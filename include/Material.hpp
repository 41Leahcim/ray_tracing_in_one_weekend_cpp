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
    const double fuzz;
public:
    inline Metal(const Color albedo_value, const double fuzz) noexcept : albedo(albedo_value), fuzz(std::min(fuzz, 1.0)) {}

    inline bool scatter(
        const Ray& ray_in, const HitRecord& record, Color& attenuation, Ray& scattered) const override
        {
        const Vec3 reflected = ray_in.direction().reflect(record.normal).unit_vector() +
            fuzz * Vec3::random_unit_vector();
        scattered = Ray(record.point, reflected);
        attenuation = albedo;
        return scattered.direction().dot(record.normal) > 0;
    }
};

class Dielectric : public Material {
private:
    // Refractive index in vacuum or air, or the ratio of the material's refractive index over
    // the refractive index of the enclosing media.
    const double refraction_index;

    /// @brief Uses Schlick's approximation for reflectance
    static constexpr double reflectance(const double cosine, const double refraction_index) noexcept {
        double r0 = (1 - refraction_index) / (1 + refraction_index);
        r0 *= r0;
        return r0 + (1 - r0) * std::pow(1 - cosine, 5);
    }

    public:
    inline constexpr Dielectric(const double refraction) noexcept : refraction_index(refraction) {}

    inline bool scatter(
        const Ray& ray_in, const HitRecord& record, Color& attenuation, Ray& scattered) const override
        {
        attenuation = Color(1.0, 1.0, 1.0);
        const double ri = record.front_face ? (1 / refraction_index) : refraction_index;

        const Vec3 unit_direction = ray_in.direction().unit_vector();
        const double cos_theta = std::fmin(record.normal.dot(-unit_direction), 1);
        const double sin_theta = std::sqrt(1 - cos_theta * cos_theta);
        
        const bool cannot_refract = ri * sin_theta > 1.0;
        const Vec3 direction = cannot_refract || reflectance(cos_theta, ri) > random_double()?
            unit_direction.reflect(record.normal) : unit_direction.refract(record.normal, ri);

        scattered = Ray(record.point, direction);
        return true;
    }
};
