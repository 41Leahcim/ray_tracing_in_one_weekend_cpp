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
    const double R = std::cos(M_PI / 4);

    const std::array<std::shared_ptr<Material>, 2> materials{
        std::make_shared<Lambertian>(Color(0, 0, 1)), // Left
        std::make_shared<Lambertian>(Color(1, 0, 0)), // Center
    };

    const HittableList world{
        std::make_shared<Sphere>(Point3(-R, 0, -1), R, materials[0]),
        std::make_shared<Sphere>(Point3(R, 0, -1), R, materials[1]),
    };

    // Create the camera and generate the image
    const Camera camera(16.0 / 9.0, 200, 100, 50, 90);
    camera.render(world);

    std::clog << seconds_since(start) << " seconds\n";
}
