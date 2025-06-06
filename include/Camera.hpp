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
    const uint16_t samples_per_pixel;  // Count of random samples for each pixel
    const double pixel_samples_scale; // Color scale factor for a sum of pixel samples.
    const uint8_t max_depth;          // Maximum number of ray bounces into scene
    const double vfov;                // Vertical view angle (field of view)
    const Point3 look_from;           // Point camera is looking from
    const Point3 look_at;             // Point camera is looking at
    const Vec3 vector_up;             // Camera-relative "up" direction
    Vec3 u, v, w;                     // Camera frame basis vectors
    const double defocus_angle;       // Variation angle of rays through each pixel
    const double focus_dist;          // Distance from camera look from point to plane of perfect focus
    Vec3 defocus_disk_u;              // Defocus disk horizontal radius
    Vec3 defocus_disk_v;              // Defocus disk vertical radius
public:
    inline Camera(
        const double aspect = 1.0,
        const uint16_t width = 100,
        const uint16_t samples = 10,
        const uint8_t depth_limit = 10,
        const double fov = 90,
        const Point3 camera_position = Point3(0, 0, 0),
        const Point3 camera_target = Point3(0, 0, -1),
        const Vec3 up_direction = Vec3(0, 1, 0),
        const double defocus_angle_value = 0,
        const double focus_distance = 10
    ) noexcept
        : samples_per_pixel(samples), pixel_samples_scale(1.0 / samples), max_depth(depth_limit),
        vfov(fov), look_from(camera_position), look_at(camera_target), vector_up(up_direction),
        defocus_angle(defocus_angle_value), focus_dist(focus_distance) {
        // Calculate the image dimensions
        aspect_ratio = aspect;
        image_width = width;
        image_height = static_cast<uint16_t>(std::fmax(image_width / aspect_ratio, 1));

        // Camera properties
        // Viewport width less than one are ok since they are real values
        const double theta = degrees_to_radians(vfov);
        const double h = std::tan(theta / 2);
        const double viewport_height = 2 * h * focus_dist;
        const double viewport_width = viewport_height * (static_cast<double>(image_width) / image_height);

        // Calculate the u, v, w unit basis vectors forthe camera coordinate frame
        w = (look_from - look_at).unit_vector();
        u = vector_up.cross(w).unit_vector();
        v = w.cross(u);

        // Calculate the vectors across horizontal and down vertical viewport edges.
        const Vec3 viewport_u = viewport_width * u;
        const Vec3 viewport_v = viewport_height * -v;

        // Calculate the horizontal and vertical delta vectors from pixel to pixel.
        pixel_delta_u = viewport_u / image_width;
        pixel_delta_v = viewport_v / image_height;

        // Calculate the location of the upper left pixel
        camera_center = look_from;
        const Vec3 viewport_upper_left = camera_center - (focus_dist * w) - viewport_u / 2
            - viewport_v / 2;
        pixel_origin_location = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

        // Calculate the camera defocus disk basis vectors
        const double defocus_radius = focus_dist * std::tan(degrees_to_radians(defocus_angle / 2));
        defocus_disk_u = u * defocus_radius;
        defocus_disk_v = v * defocus_radius;
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

    /// @brief Returns a random point in the camera defocus disk
    inline Point3 defocus_disk_sample() const {
        const Point3 point = Point3::random_in_unit_disk();
        return camera_center + point[0] * defocus_disk_u + point[1] * defocus_disk_v;
    }

    /// Constructs a camera ray originating from the defocus disk and directed at a randomly
    /// sampled point around the pixel location x, y
    inline Ray get_ray(const int32_t x, const int32_t y) const {
        const Vec3 offset = sample_square();
        const Point3 pixel_sample = pixel_origin_location
            + (x + offset.x()) * pixel_delta_u
            + (y + offset.y()) * pixel_delta_v;

        const Point3 ray_origin = defocus_angle <= 0? camera_center : defocus_disk_sample();
        const Vec3 ray_direction = pixel_sample - ray_origin;

        return Ray(ray_origin, ray_direction);
    }

    inline void render(const Hittable& world) const {
        // Render the image
        std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
        for(uint16_t y = 0;y < image_height;y++){
            for(uint16_t x = 0;x < image_width;x++){
                std::clog << '\r' << (image_height - y) << " lines remaining " << (image_width - x) << " pixels remaining ";
                Color pixel_color(0, 0, 0);
                for(uint16_t sample = 0;sample < samples_per_pixel;sample++){
                    const Ray ray = get_ray(x, y);
                    pixel_color += ray_color(ray, max_depth, world);
                }
                write_color(std::cout, pixel_samples_scale * pixel_color);
            }
        }
        std::clog << "\nDone.\n";
    }
};
