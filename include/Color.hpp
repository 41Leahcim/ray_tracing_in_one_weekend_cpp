#pragma once

#include "Vec3.hpp"

using Color = Vec3;

inline std::ostream& write_color(std::ostream& out, const Color& pixel_color){
    const uint16_t red = static_cast<uint8_t>(255.999 * pixel_color.x());
    const uint16_t green = static_cast<uint8_t>(255.999 * pixel_color.y());
    const uint16_t blue = static_cast<uint8_t>(255.999 * pixel_color.z());

    out << red << ' ' << green << ' ' << blue << '\n';
    return out;
}
