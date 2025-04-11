#pragma once

#include "Hittable.hpp"
#include "Color.hpp"
#include "util.hpp"
#include "Material.hpp"

#include <cinttypes>
#include <iostream>

class Camera{
private:
    uint16_t image_height;            // Rendered image height
    Point3 camera_center;             // Camera center
    Point3 pixel_origin_location;     // Location of pixel 0, 0
    Vec3 pixel_delta_u;               // Offset to pixel to the right
    Vec3 pixel_delta_v;               // Offset to pixel below
    double aspect_ratio;              // Ratio of image width and height
    uint16_t image_width;             // Rendered image width in pixel count
    const uint8_t samples_per_pixel;  // Count of random samples for each pixel
    const double pixel_samples_scale; // Color scale factor for a sum of pixel samples.
    const uint8_t max_depth = 10;     // Maximum number of ray bounces into scene
public:
    inline Camera(
        const double aspect = 1.0,
        const uint16_t width = 100,
        const uint8_t samples = 10,
        const uint8_t depth_limit = 50) noexcept
        : samples_per_pixel(samples), pixel_samples_scale(1.0 / samples), max_depth(depth_limit) {
        // Calculate the image dimensions
        aspect_ratio = aspect;
        image_width = width;
        image_height = static_cast<uint16_t>(std::fmax(image_width / aspect_ratio, 1));

        // Camera properties
        // Viewport width less than one are ok since they are real values
        const double focal_length = 1.0;
        const double viewport_height = 2.0;
        const double viewport_width = viewport_height * (static_cast<double>(image_width) / image_height);

        // Calculate the vectors across horizontal and down vertical viewport edges.
        const Vec3 viewport_u(viewport_width, 0, 0);
        const Vec3 viewport_v(0, -viewport_height, 0);

        // Calculate the horizontal and vertical delta vectors from pixel to pixel.
        pixel_delta_u = viewport_u / image_width;
        pixel_delta_v = viewport_v / image_height;

        // Calculate the location of the upper left pixel
        camera_center = Point3(0, 0, 0);
        const Vec3 viewport_upper_left = camera_center - Vec3(0, 0, focal_length) - viewport_u / 2
            - viewport_v / 2;
        pixel_origin_location = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
    }

    inline Color ray_color(const Ray& ray, const uint8_t depth_left, const Hittable& world) const noexcept {
        // If the ray bounce limit is reached, no more light is gathered
        if(depth_left == 0){
            return Color(0, 0, 0);
        }

        HitRecord record;
        if(world.hit(ray, Interval(0.001, INFINITY), record)){
            Ray scattered;
            Color attenuation;
            if(record.material->scatter(ray, record, attenuation, scattered)){
                return attenuation * ray_color(scattered, depth_left - 1, world);
            }
            return Color(0, 0, 0);
        }

        const Vec3 unit_direction = ray.direction().unit_vector();
        const double a = 0.5 * (unit_direction.y() + 1.0);
        return (1.0 - a) * Color(1, 1, 1) + a * Color(0.5, 0.7, 1);
    }

    /// Returns the vector to a random point in the [-.5, -.5]-[.5, .5] unit square.
    inline Vec3 sample_square() const {
        return Vec3(random_double() - 0.5, random_double() - 0.5, 0);
    }

    /// Constructs a camera ray originating from the origin at randomly samples points around the
    /// pixel location x, y
    Ray get_ray(const int32_t x, const int32_t y) const {
        const Vec3 offset = sample_square();
        const Point3 pixel_sample = pixel_origin_location
            + (x + offset.x()) * pixel_delta_u
            + (y + offset.y()) * pixel_delta_v;

        const Point3 ray_origin = camera_center;
        const Vec3 ray_direction = pixel_sample - ray_origin;

        return Ray(ray_origin, ray_direction);
    }

    inline void render(const Hittable& world) const {
        // Render the image
        std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
        for(uint16_t y = 0;y < image_height;y++){
            std::clog << "\rScanlines remaining: " << (image_height - y) << ' ';
            for(uint16_t x = 0;x < image_width;x++){
                Color pixel_color(0, 0, 0);
                for(uint8_t sample = 0;sample < samples_per_pixel;sample++){
                    const Ray ray = get_ray(x, y);
                    pixel_color += ray_color(ray, max_depth, world);
                }
                write_color(std::cout, pixel_samples_scale * pixel_color);
            }
        }
        std::clog << "\rDone.                 \n";
    }
};
