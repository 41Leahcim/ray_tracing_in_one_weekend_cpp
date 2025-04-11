#pragma once

#include <cmath>
#include <random>

inline double degrees_to_radians(const double degrees) noexcept {
    return degrees * M_PI_2;
}

/// @brief Returns a random real in [0, 1) (0 inclusive, 1 exclusive).
inline double random_double(){
    static std::uniform_real_distribution<double> distribution;
    static std::mt19937 generator;
    return distribution(generator);
}

/// @brief Returns a random real in [min, max) (min inclusive, max exclusive).
inline double random_double(const double min, const double max){
    return min + (max - min) * random_double();
}
