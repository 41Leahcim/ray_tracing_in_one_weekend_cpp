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
    const std::shared_ptr<Lambertian> ground_material =
        std::make_shared<Lambertian>(Color(0.5, 0.5, 0.5));
    HittableList world(std::make_shared<Sphere>(Point3(0, -1000, 0), 1000, ground_material));

    for(int8_t a = -11;a < 11;a++){
        for(int8_t b = -11;b < 11;b++){
            const double choose_mat = random_double();
            const Point3 center(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());

            if((center - Point3(4, 0.2, 0)).length() > 0.9){
                std::shared_ptr<Material> sphere_material;

                if(choose_mat < 0.8){
                    // Diffuse
                    const Color albedo = Color::random() - Color::random();
                    sphere_material = std::make_shared<Lambertian>(albedo);
                    world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
                }else if(choose_mat < 0.95){
                    // Metal
                    const Color albedo = Color::random(0.5, 1);
                    const double fuzz = random_double(0, 0.5);
                    sphere_material = std::make_shared<Metal>(albedo, fuzz);
                    world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
                }else{
                    // Glass
                    sphere_material = std::make_shared<Dielectric>(1.5);
                    world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    const std::shared_ptr<Dielectric> material1 = std::make_shared<Dielectric>(1.5);
    world.add(std::make_shared<Sphere>(Point3(0, 1, 0), 1.0, material1));
    
    const std::shared_ptr<Lambertian> material2 = std::make_shared<Lambertian>(Color(0.4, 0.2, 0.1));
    world.add(std::make_shared<Sphere>(Point3(-4, 1, 0), 1.0, material2));

    const std::shared_ptr<Metal> material3 = std::make_shared<Metal>(Color(0.7, 0.6, 0.5), 0);
    world.add(std::make_shared<Sphere>(Point3(4, 1, 0), 1, material3));

    // Create the camera and generate the image
    const Camera camera(
        16.0 / 9.0,
        1200,
        500,
        50,
        20,
        Point3(13, 2, 3),
        Point3(0, 0, 0),
        Vec3(0, 1, 0),
        0.6,
        10
    );
    camera.render(world);

    std::clog << seconds_since(start) << " seconds\n";
}
