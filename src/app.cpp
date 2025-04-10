#include <iostream>
#include <cstdint>
#include <chrono>

#include "Vec3.hpp"
#include "Color.hpp"
#include "Ray.hpp"
#include "Sphere.hpp"
#include "HittableList.hpp"

namespace chrono = std::chrono;
using chrono::steady_clock;

inline double seconds_since(const steady_clock::time_point start) {
    return static_cast<double>((steady_clock::now() - start).count()) /
        (chrono::seconds(1) / chrono::nanoseconds(1));
}

inline Color ray_color(const Ray& ray, const Hittable& world) noexcept {
    HitRecord record;
    if(world.hit(ray, 0, INFINITY, record)){
        return 0.5 * (record.normal + Color(1, 1, 1));
    }

    const Vec3 unit_direction = ray.direction().unit_vector();
    const double a = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - a) * Color(1, 1, 1) + a * Color(0.5, 0.7, 1);
}

int main(){
    const steady_clock::time_point start = steady_clock::now();

    // Calculate the image dimensions
    const double aspect_ratio = 16.0 / 9.0;
    const uint16_t image_width = 2160;
    const uint16_t image_height = static_cast<uint16_t>(std::fmax(image_width / aspect_ratio, 1));

    // World
    HittableList world(std::make_shared<Sphere>(Point3(0, 0, -1), 0.5));
    world.add(std::make_shared<Sphere>(Point3(0, -100.5, -1), 100));

    // Camera properties
    // Viewport width less than one are ok since they are real values
    const double focal_length = 1.0;
    const double viewport_height = 2.0;
    const double viewport_width = viewport_height * (static_cast<double>(image_width) / image_height);
    const Point3 camera_center;

    // Calculate the vectors across horizontal and down vertical viewport edges.
    const Vec3 viewport_u(viewport_width, 0, 0);
    const Vec3 viewport_v(0, -viewport_height, 0);

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    const Vec3 pixel_delta_u = viewport_u / image_width;
    const Vec3 pixel_delta_v = viewport_v / image_height;

    // Calculate the location of the upper left pixel
    const Vec3 viewport_upper_left = camera_center - Vec3(0, 0, focal_length) - viewport_u / 2 -
        viewport_v / 2;
    const Point3 pixel_origin_location = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    // Render the image
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    for(uint16_t y = 0;y < image_height;y++){
        std::clog << "\rScanlines remaining: " << (image_height - y) << ' ';
        for(uint16_t x = 0;x < image_width;x++){
            const Point3 pixel_center = pixel_origin_location + (x * pixel_delta_u) +
                (y * pixel_delta_v);
            const Vec3 ray_direction = pixel_center - camera_center;
            const Ray ray(camera_center, ray_direction);
            const Color pixel_color = ray_color(ray, world);
            write_color(std::cout, pixel_color);
        }
    }
    std::clog << "\rDone.                 \n";
    std::clog << seconds_since(start) << " seconds\n";
}
