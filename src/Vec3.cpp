#include "Vec3.hpp"

#include <cmath>

Vec3::Vec3() : elements{0, 0, 0}{}

Vec3::Vec3(double element0, double element1, double element2) :
    elements{element0, element1, element2}{}

double Vec3::x() const{
    return elements[0];
}

double Vec3::y() const{
    return elements[1];
}

double Vec3::z() const{
    return elements[2];
}

Vec3 Vec3::operator-() const{
    return Vec3(-elements[0], -elements[1], -elements[2]);
}

double Vec3::operator[](size_t index) const{
    return elements[index];
}

double& Vec3::operator[](size_t index){
    return elements[index];
}

Vec3 Vec3::operator+(const Vec3& other) const{
    return Vec3(this->elements[0] + other.elements[0], this->elements[1] + other.elements[1], this->elements[2] + other.elements[2]);
}

Vec3 Vec3::operator-(const Vec3& other) const{
    return Vec3(this->elements[0] - other.elements[0], this->elements[1] - other.elements[1], this->elements[2] - other.elements[2]);
}

Vec3 Vec3::operator*(const Vec3& other) const{
    return Vec3(this->elements[0] * other.elements[0], this->elements[1] * other.elements[1], this->elements[2] * other.elements[2]);
}

Vec3 Vec3::operator*(const double times) const{
    return Vec3(this->elements[0] * times, this->elements[1] * times, this->elements[2] * times);
}

Vec3 Vec3::operator/(const double times) const{
    return Vec3(this->elements[0] / times, this->elements[1] / times, this->elements[2] / times);
}

double Vec3::dot(const Vec3& other) const{
    return this->elements[0] * other.elements[0] +
           this->elements[1] * other.elements[1] +
           this->elements[2] * other.elements[2];
}

Vec3 Vec3::cross(const Vec3& other) const{
    return Vec3(this->elements[1] * other.elements[2] - this->elements[2] * other.elements[1],
                this->elements[2] * other.elements[0] - this->elements[0] * other.elements[2],
                this->elements[0] * other.elements[1] - this->elements[1] * other.elements[0]);
}

Vec3& Vec3::operator+=(const Vec3& other){
    for(size_t i = 0;i < 3;i++){
        this->elements[i] += other.elements[i];
    }
    return *this;
}

Vec3& Vec3::operator*=(const double times){
    for(size_t i = 0;i < 3;i++){
        this->elements[i] *= times;
    }
    return *this;
}

Vec3& Vec3::operator/=(const double times){
    for(size_t i = 0;i < 3;i++){
        this->elements[i] /= times;
    }
    return *this;
}

double Vec3::length() const{
    return std::sqrt(length_squared());
}

double Vec3::length_squared() const{
    return elements[0] * elements[0] + elements[1] * elements[1] + elements[2] * elements[2];
}

Vec3 Vec3::unit_vector() const{
    return *this / this->length();
}

Vec3 operator*(const double t, const Vec3& vector){
    return vector * t;
}
