#include <iostream>
#include <cstdint>
#include <chrono>

#include "Vec3.hpp"
#include "Color.hpp"

namespace chrono = std::chrono;
using chrono::steady_clock;

double seconds_since(const steady_clock::time_point start){
    return static_cast<double>((steady_clock::now() - start).count()) /
        (chrono::seconds(1) / chrono::nanoseconds(1));
}

int main(){
    const steady_clock::time_point start = steady_clock::now();

    // Image dimensions
    const uint16_t image_width = 1024;
    const uint16_t image_height = 1024;

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
