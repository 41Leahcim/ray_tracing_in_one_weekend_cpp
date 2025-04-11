#pragma once

#include "Vec3.hpp"
#include "Interval.hpp"

using Color = Vec3;

inline double linear_to_gamma(const double linear_component){
    return linear_component > 0? std::sqrt(linear_component) : 0;
}

inline std::ostream& write_color(std::ostream& out, const Color& pixel_color){
    static const Interval intensity(0, 0.999);
    const uint16_t red = static_cast<uint8_t>(256 *  intensity.clamp(linear_to_gamma(pixel_color.x())));
    const uint16_t green = static_cast<uint8_t>(256 * intensity.clamp(linear_to_gamma(pixel_color.y())));
    const uint16_t blue = static_cast<uint8_t>(256 * intensity.clamp(linear_to_gamma(pixel_color.z())));

    out << red << ' ' << green << ' ' << blue << '\n';
    return out;
}
