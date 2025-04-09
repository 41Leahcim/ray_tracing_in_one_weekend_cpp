#pragma once

#include <ostream>
#include <array>
#include <cmath>

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
};

inline Vec3 operator*(const double time, const Vec3& vec) noexcept {
    return vec * time;
}

inline std::ostream& operator<<(std::ostream& out, const Vec3& vec){
    out << vec[0] << ' ' << vec[1] << ' ' << vec[2];
    return out;
}

using Point3 = Vec3;
