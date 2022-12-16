#pragma once

#include <cstddef>
#include <ostream>

class Vec3{
public:
    Vec3();
    Vec3(double element0, double element1, double element2);

    double x() const;
    double y() const;
    double z() const;

    Vec3 operator-() const;
    double operator[](size_t index) const;
    double& operator[](size_t index);

    Vec3 operator+(const Vec3& other) const;
    Vec3 operator-(const Vec3& other) const;
    Vec3 operator*(const Vec3& other) const;

    Vec3 operator*(const double times) const;
    Vec3 operator/(const double times) const;

    double dot(const Vec3& other) const;
    Vec3 cross(const Vec3& other) const;

    Vec3& operator+=(const Vec3& other);
    Vec3& operator*=(const double times);
    Vec3& operator/=(const double times);

    double length() const;
    double length_squared() const;
    Vec3 unit_vector() const;
private:
    double elements[3];
};

// Type aliases for Vec3
using Point3 = Vec3; // 3D point
using Color = Vec3;  // RGB color

std::ostream& operator<<(std::ostream &out, const Vec3 &vector);

Vec3 operator*(const double t, const Vec3& vector);
