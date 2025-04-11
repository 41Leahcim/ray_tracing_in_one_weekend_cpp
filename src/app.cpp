#include <iostream>
#include <cstdint>
#include <chrono>

#include "Vec3.hpp"
#include "Color.hpp"
#include "Ray.hpp"
#include "Sphere.hpp"
#include "HittableList.hpp"
#include "Camera.hpp"

namespace chrono = std::chrono;
using chrono::steady_clock;

inline double seconds_since(const steady_clock::time_point start) {
    return static_cast<double>((steady_clock::now() - start).count()) /
        (chrono::seconds(1) / chrono::nanoseconds(1));
}

int main(){
    const steady_clock::time_point start = steady_clock::now();

    // World
    const std::array<std::shared_ptr<Material>, 5> materials{
        std::make_shared<Lambertian>(Color(0.8, 0.8, 0)), // Ground
        std::make_shared<Lambertian>(Color(0.1, 0.2, 0.5)), // Center
        std::make_shared<Dielectric>(1.5), // Left
        std::make_shared<Dielectric>(1 / 1.5), // Bubble
        std::make_shared<Metal>(Color(0.8, 0.6, 0.2), 1.0), // Right
    };

    HittableList world{
        std::make_shared<Sphere>(Point3(0, -100.5, -1), 100, materials[0]),
        std::make_shared<Sphere>(Point3(0, 0, -1.2), 0.5, materials[1]),
        std::make_shared<Sphere>(Point3(-1, 0, -1), 0.5, materials[2]),
        std::make_shared<Sphere>(Point3(-1, 0, -1), 0.4, materials[3]),
        std::make_shared<Sphere>(Point3(1, 0, -1), 0.5, materials[4]),
    };

    // Create the camera and generate the image
    const Camera camera(16.0 / 9.0, 200, 100, 50);
    camera.render(world);

    std::clog << seconds_since(start) << " seconds\n";
}
