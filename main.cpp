#include <iostream>
#include "ColorUtil.h"
#include "Ray.h"
#include "vec3.h"
#include "Vec3Util.h"
#include "rtweekendutil.h"

#include "HittableList.h"
#include "sphere.h"
#include "Camera.h"
#include "Material.h"
#include "Lambertian.h"
#include "Metal.h"
#include "Dielectric.h"

using namespace rtweekend_math;
HittableList random_scene() {
    HittableList world;

    auto ground_material = make_shared<Lambertian>(Color(0.5, 0.5, 0.5));
    world.add(make_shared<Sphere>(Point3(0, -1000, 0), 1000, ground_material));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = RandomDouble();
            Point3 center(a + 0.9 * RandomDouble(), 0.2, b + 0.9 * RandomDouble());

            if ((center - Point3(4, 0.2, 0)).Length() > 0.9) {
                shared_ptr<Material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = random() * random();
                    sphere_material = make_shared<Lambertian>(albedo);
                    world.add(make_shared<Sphere>(center, 0.2, sphere_material));
                }
                else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = random(0.5, 1);
                    auto fuzz = RandomDouble(0, 0.5);
                    sphere_material = make_shared<Metal>(albedo, fuzz);
                    world.add(make_shared<Sphere>(center, 0.2, sphere_material));
                }
                else {
                    // glass
                    sphere_material = make_shared<Dielectric>(1.5);
                    world.add(make_shared<Sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = make_shared<Dielectric>(1.5);
    world.add(make_shared<Sphere>(Point3(0, 1, 0), 1.0, material1));

    auto material2 = make_shared<Lambertian>(Color(0.4, 0.2, 0.1));
    world.add(make_shared<Sphere>(Point3(-4, 1, 0), 1.0, material2));

    auto material3 = make_shared<Metal>(Color(0.7, 0.6, 0.5), 0.0);
    world.add(make_shared<Sphere>(Point3(4, 1, 0), 1.0, material3));

    return world;
}

double HitSphere(const Point3 center, double radius, const Ray& r) {
    Vec3 modifiedCenter = r.origin() - center;
    auto a = r.direction().LengthSquared();
    auto half_b = dot(modifiedCenter, r.direction());
    auto c = modifiedCenter.LengthSquared() - radius * radius;
    auto discriminant = half_b * half_b - a * c;
    if (discriminant < 0) {
        return -1.0;
    }
    else {
        return (-half_b - sqrt(discriminant)) / a;
    }
}

Color ray_color(const Ray& r, const Hittable& world, int depth) {

    if (depth == 0) {
        return Color(0, 0, 0);
    }
    hitRecord record;

    if (world.hit(r, 0.001, infinity, record)) {
        Ray scattered;
        Color attenuation;
        if (record.materialPointer->scatter(r, record, attenuation, scattered)) {
            return attenuation * ray_color(scattered, world, depth - 1);
        }
        return Color(0, 0, 0);
    }

    Vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
}

int main() {

    // Image
    const auto kAspectRatio = 16.0 / 9.0;
    const int kImageWidth = 1600;
    const int kImageHeight = static_cast<int> (kImageWidth / kAspectRatio);
    const int samplesPerPixel = 200;
    const int maxDepth = 30;

    //world
    auto R = cos(pi / 4);

    auto world = random_scene();


    Point3 lookfrom(13, 2, 3);
    Point3 lookat(0, 0, 0);
    Vec3 vup(0, 1, 0);
    auto dist_to_focus = 10;
    auto aperture = .1;


    Camera cam(lookfrom, lookat, vup, 20, kAspectRatio, aperture, dist_to_focus);
    // Render

    std::cout << "P3\n" << kImageWidth << ' ' << kImageHeight << "\n255\n";

    for (int j = kImageHeight - 1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < kImageWidth; ++i) {
            Color pixel_color(0, 0, 0);
            for (int s = 0; s < samplesPerPixel; ++s) {
                auto u = (i + RandomDouble()) / (kImageWidth - 1);
                auto v = (j + RandomDouble()) / (kImageHeight - 1);
                Ray r = cam.getRay(u, v);
                pixel_color += ray_color(r, world, maxDepth);
            }
            ColorUtil::WriteColor(std::cout, pixel_color, samplesPerPixel);
        }
    }
    std::cerr << "\nDone.\n";
}