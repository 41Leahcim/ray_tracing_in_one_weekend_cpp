#include <iostream>
#include <cstdint>
#include <chrono>

#include "Vec3.hpp"
#include "Color.hpp"
#include "Ray.hpp"

namespace chrono = std::chrono;
using chrono::steady_clock;

inline constexpr double max(const double left, const double right) noexcept {
    return left > right ? left : right;
}

inline double seconds_since(const steady_clock::time_point start) {
    return static_cast<double>((steady_clock::now() - start).count()) /
        (chrono::seconds(1) / chrono::nanoseconds(1));
}

inline Color ray_color(const Ray& ray) noexcept {
    return Color(0, 0, 0);
}

int main(){
    const steady_clock::time_point start = steady_clock::now();

    // Calculate the image dimensions
    const double aspect_ratio = 16.0 / 9.0;
    const uint16_t image_width = 1080;
    const uint16_t image_height = static_cast<uint16_t>(max(image_height / aspect_ratio, 1));

    // Viewport width less than one are ok since they are real values
    const double viewport_height = 2.0;
    const double viewport_width = viewport_height * (static_cast<double>(image_width) / image_height);

    // Render the image
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    for(uint16_t y = 0;y < image_height;y++){
        std::clog << "\rScanlines remaining: " << (image_height - y) << ' ';
        for(uint16_t x = 0;x < image_width;x++){
            const Color pixel_color = Color(
                static_cast<double>(x) / (image_width - 1),
                static_cast<double>(y) / (image_height - 1),
                0
            );
            write_color(std::cout, pixel_color);
        }
    }
    std::clog << "\rDone.                 \n";
    std::clog << seconds_since(start) << " seconds\n";
}
