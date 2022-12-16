#include <iostream>
#include <chrono>

#include "Color.hpp"
#include "Vec3.hpp"

using std::chrono::time_point;
using std::chrono::steady_clock;
using std::chrono::duration;
using std::chrono::microseconds;
using std::chrono::seconds;
using std::chrono::duration_cast;

int main(){
    // Start measuring performance
    time_point<steady_clock> start = steady_clock::now();

    // Image properties
    const int IMAGE_WIDTH = 4096;
    const int IMAGE_HEIGHT = 4096;

    // Rendering
    std::cout << "P3\n" << IMAGE_WIDTH << ' ' << IMAGE_HEIGHT << "\n255\n";

    for(int y = IMAGE_HEIGHT - 1;y >= 0;y--){
        std::cerr << "\rScanlines remaining: " << y << ' ' << std::flush;
        for(int x = 0;x < IMAGE_HEIGHT;x++){
            Color pixel_color(
                static_cast<double>(x) / (IMAGE_WIDTH - 1),
                static_cast<double>(y) / (IMAGE_HEIGHT - 1),
                0.25);

            write_color(std::cout, pixel_color);
        }
    }

    std::cerr << "\nDone.\n";

    time_point<steady_clock> done = steady_clock::now();
    microseconds performance = duration_cast<microseconds>(done - start);
    std::cerr << static_cast<double>(performance.count()) / duration_cast<microseconds>(seconds(1)).count() << '\n';
}
