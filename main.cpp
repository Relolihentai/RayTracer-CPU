#include "library.h"

#include "ray.h"
#include "sceneObjectList.h"
#include "sphere.h"
#include "camera.h"
#include "material.h"

#include <iostream>
vec3 ray_color(const ray& r, const sceneObjectList& world, int depth) {
    hit_record rec;

    if (depth <= 0)
        return vec3(1, 0, 0);

    if (world.hit(r, 0.001, Infinity, rec)) {
        ray scattered;
        vec3 attenuation;
        if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
            return attenuation * ray_color(scattered, world, depth - 1);
        return vec3(0, 0, 0);
    }

    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5*(unit_direction.y() + 1.0);
    return (1.0-t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
}

int main() {
    const int image_width = 1920;
    const int image_height = 1080;
    const int samples_per_pixel = 100;
    const int max_depth = 50;
    const auto aspect_ratio = double(image_width) / image_height;

    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    sceneObjectList world;
    world.add(std::make_shared<sphere>(
        vec3(0,-100.5,-1), 100, std::make_shared<lambertian>(vec3(0.8, 0.8, 0.0))));
    world.add(std::make_shared<sphere>(vec3(0, 0.5, 0), 1.0, std::make_shared<dielectric>(1.5)));

    world.add(
        std::make_shared<sphere>(vec3(-4, 0.5, 0), 1.0, std::make_shared<lambertian>(vec3(0.4, 0.2, 0.1))));

    world.add(
        std::make_shared<sphere>(vec3(4, 0.5, 0), 1.0, std::make_shared<metal>(vec3(0.7, 0.6, 0.5), 0.0)));
    world.add(
        std::make_shared<sphere>(vec3(4, -0.3, 2), 0.2, std::make_shared<lambertian>(vec3(0.4, 0.2, 0.1))));
    world.add(
        std::make_shared<sphere>(vec3(4, -0.3, -2), 0.2, std::make_shared<metal>(vec3(0.7, 0.6, 0.5), 0.0)));
    world.add(
        std::make_shared<sphere>(vec3(3, -0.3, -3.5), 0.3, std::make_shared<lambertian>(vec3(0.8, 0.8, 0.0))));
    world.add(
        std::make_shared<sphere>(vec3(3, -0.3, 3.5), 0.35, std::make_shared<metal>(vec3(0.7, 0.6, 0.5), 0.0)));

    vec3 lookfrom(13,2,3);
    vec3 lookat(0,0,0);
    vec3 vup(0,1,0);
    auto dist_to_focus = 10.0;
    auto aperture = 0.1;

    camera cam(lookfrom, lookat, vup, 20, aspect_ratio, aperture, dist_to_focus);

    for (int j = image_height-1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            vec3 color(0, 0, 0);
            for (int s = 0; s < samples_per_pixel; ++s) {
                auto u = (i + random_double()) / image_width;
                auto v = (j + random_double()) / image_height;
                ray r = cam.get_ray(u, v);
                color += ray_color(r, world, max_depth);
            }
            color.write_color(std::cout, samples_per_pixel);
        }
    }

    std::cerr << "\nDone.\n";
}