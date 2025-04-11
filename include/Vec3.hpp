#pragma once

#include <ostream>
#include <array>
#include <cmath>

#include "Interval.hpp"
#include "util.hpp"

class Vec3{
private:
    std::array<double, 3> elements;
public:
    inline constexpr Vec3() noexcept : elements{0, 0, 0} {}
    inline constexpr Vec3(const double e0, const double e1, const double e2) noexcept :
        elements{e0, e1, e2} {}
    inline virtual ~Vec3() noexcept {}

    inline constexpr double x() const noexcept{
        return elements[0];
    }

    inline constexpr double y() const noexcept{
        return elements[1];
    }

    inline constexpr double z() const noexcept{
        return elements[2];
    }

    inline Vec3 operator-() const noexcept {
        return Vec3(-elements[0], -elements[1], -elements[2]);
    }

    inline double operator[](const size_t index) const{
        return elements.at(index);
    }

    inline double& operator[](const size_t index) {
        return elements.at(index);
    }

    inline Vec3 operator+(const Vec3& other) const noexcept{
        Vec3 result = *this;
        result += other;
        return result;
    }

    inline constexpr Vec3& operator+=(const Vec3& other) noexcept{
        elements[0] += other.elements[0];
        elements[1] += other.elements[1];
        elements[2] += other.elements[2];
        return *this;
    }

    inline Vec3 operator-(const Vec3& other) const noexcept{
        Vec3 result = *this;
        result -= other;
        return result;
    }

    inline constexpr Vec3& operator-=(const Vec3& other) noexcept{
        elements[0] -= other.elements[0];
        elements[1] -= other.elements[1];
        elements[2] -= other.elements[2];
        return *this;
    }

    inline Vec3 operator*(const Vec3& other) const noexcept{
        Vec3 result = *this;
        result *= other;
        return result;
    }

    inline constexpr Vec3& operator*=(const Vec3& other) noexcept{
        elements[0] *= other.elements[0];
        elements[1] *= other.elements[1];
        elements[2] *= other.elements[2];
        return *this;
    }

    inline constexpr Vec3& operator/=(const double time) noexcept {
        elements[0] /= time;
        elements[1] /= time;
        elements[2] /= time;
        return *this;
    }

    inline Vec3 operator/(const double time) const noexcept{
        Vec3 result = *this;
        result /= time;
        return result;
    }
    
    inline constexpr Vec3& operator*=(const double time) noexcept {
        elements[0] *= time;
        elements[1] *= time;
        elements[2] *= time;
        return *this;
    }

    inline Vec3 operator*(const double time) const noexcept{
        Vec3 result = *this;
        result *= time;
        return result;
    }

    inline constexpr double length_squared() const noexcept {
        return elements[0] * elements[0] + elements[1] * elements[1] + elements[2] * elements[2];
    }

    inline constexpr double length() const noexcept {
        return std::sqrt(length_squared());
    }

    inline constexpr double dot(const Vec3& other) const noexcept {
        return elements[0] * other.elements[0] + elements[1] * other.elements[1] + elements[2] *
            other.elements[2];
    }

    inline Vec3 cross(const Vec3& other) const noexcept {
        return Vec3(
            elements[1] * other.elements[2] - elements[2] * other.elements[1],
            elements[2] * other.elements[0] - elements[0] * other.elements[2],
            elements[0] * other.elements[1] - elements[1] * other.elements[0]
        );
    }

    inline Vec3 unit_vector() const noexcept {
        return *this / length();
    }

    inline static Vec3 random() {
        return Vec3(random_double(), random_double(), random_double());
    }

    inline static Vec3 random(const double minimum, const double maximum) {
        return Vec3(random_double(minimum, maximum), random_double(minimum, maximum), random_double(minimum, maximum));
    }

    inline static Vec3 random_unit_vector() {
        while(true){
            const Vec3 point = random(-1, 1);
            const double length_squared = point.length_squared();
            if(Interval(1e-160, 1).contains(length_squared)){
                return point / std::sqrt(length_squared);
            }
        }
    }

    inline Vec3 random_on_hemisphere() const {
        const Vec3 on_unit_sphere = random_unit_vector();

        // In the same hemisphere as the normal
        if(on_unit_sphere.dot(*this) > 0.0){
            return on_unit_sphere;
        }else{
            return -on_unit_sphere;
        }
    }

    /// @brief Returns true if the vector is close to zero in all dimensions.
    inline bool near_zero() const noexcept {
        const double s = 1e-8;
        for(const double element : elements){
            if(std::fabs(element) >= s){
                return false;
            }
        }
        return true;
    }

    inline Vec3 reflect(const Vec3& n) const noexcept {
        return *this - n * (2 * this->dot(n));
    }

    inline Vec3 refract(const Vec3& n, const double etai_over_etat) const {
        const double cos_theta = std::fmin((-*this).dot(n), 1);
        const Vec3 r_out_perp = (*this + n * cos_theta) * etai_over_etat;
        const Vec3 r_out_parallel = n * -std::sqrt(std::abs(1.0 - r_out_perp.length_squared()));
        return r_out_perp + r_out_parallel;
    }
};

inline Vec3 operator*(const double time, const Vec3& vec) noexcept {
    return vec * time;
}

inline std::ostream& operator<<(std::ostream& out, const Vec3& vec){
    out << vec[0] << ' ' << vec[1] << ' ' << vec[2];
    return out;
}

using Point3 = Vec3;
