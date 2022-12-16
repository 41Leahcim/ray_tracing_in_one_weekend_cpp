#include <iostream>
#include <chrono>

#include "Color.hpp"
#include "Vec3.hpp"
#include "Ray.hpp"

using std::chrono::time_point;
using std::chrono::steady_clock;
using std::chrono::duration;
using std::chrono::microseconds;
using std::chrono::seconds;
using std::chrono::duration_cast;

Color ray_color(const Ray& ray){
    Vec3 unit_direction = ray.direction().unit_vector();
    double time = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - time) * Color(1.0, 1.0, 1.0) + time * Color(0.5, 0.7, 1.0);
}

int main(){
    // Start measuring performance
    time_point<steady_clock> start = steady_clock::now();

    // Image properties
    const double ASPECT_RATION = 16.0 / 9.0;
    const int IMAGE_WIDTH = 4096;
    const int IMAGE_HEIGHT = static_cast<int>(IMAGE_WIDTH / ASPECT_RATION);

    // Camera
    const double VIEWPORT_HEIGHT = 2.0;
    const double VIEWPORT_WIDTH = ASPECT_RATION * VIEWPORT_HEIGHT;
    const double FOCAL_LENGTH = 1.0;

    Point3 origin(0.0, 0.0, 0.0);
    Vec3 horizontal(VIEWPORT_WIDTH, 0.0, 0.0);
    Vec3 vertical(0.0, VIEWPORT_HEIGHT, 0.0);
    Point3 lower_left_corner = origin - horizontal / 2.0 - vertical / 2.0 - Vec3(0.0, 0.0, FOCAL_LENGTH);

    // Rendering
    std::cout << "P3\n" << IMAGE_WIDTH << ' ' << IMAGE_HEIGHT << "\n255\n";

    for(int y = IMAGE_HEIGHT - 1;y >= 0;y--){
        std::cerr << "\rScanlines remaining: " << y << ' ' << std::flush;
        for(int x = 0;x < IMAGE_HEIGHT;x++){
            double u = static_cast<double>(x) / (IMAGE_WIDTH - 1);
            double v = static_cast<double>(y) / (IMAGE_HEIGHT - 1);
            Ray ray(origin, lower_left_corner + u * horizontal + v * vertical - origin);
            Color pixel_color = ray_color(ray);
            write_color(std::cout, pixel_color);
        }
    }

    std::cerr << "\nDone.\n";

    time_point<steady_clock> done = steady_clock::now();
    microseconds performance = duration_cast<microseconds>(done - start);
    std::cerr << static_cast<double>(performance.count()) / duration_cast<microseconds>(seconds(1)).count() << '\n';
}
