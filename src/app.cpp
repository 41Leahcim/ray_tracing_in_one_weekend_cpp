#include <iostream>
#include <cstdint>
#include <chrono>

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
            const double red = static_cast<uint8_t>(
                static_cast<double>(x) / (image_width - 1) * 255.999
            );
            const double green = static_cast<uint8_t>(
                static_cast<double>(y) / (image_height - 1) * 255.999
            );
            const double blue = 0.0;

            std::cout << red << ' ' << green << ' ' << blue << '\n';
        }
    }
    std::clog << "\rDone.                 \n";
    std::clog << seconds_since(start) << " seconds\n";
}
