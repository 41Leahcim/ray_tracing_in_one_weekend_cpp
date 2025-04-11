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
    HittableList world(std::make_shared<Sphere>(Point3(0, 0, -1), 0.5));
    world.add(std::make_shared<Sphere>(Point3(0, -100.5, -1), 100));

    // Create the camera and generate the image
    const Camera camera(16.0 / 9.0, 400, 100, 50);
    camera.render(world);

    std::clog << seconds_since(start) << " seconds\n";
}
