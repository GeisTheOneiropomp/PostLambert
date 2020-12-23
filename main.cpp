#include <iostream>
#include "ColorUtil.h"
#include "Ray.h"
#include "vec3.h"
#include "Vec3Util.h"
#include "rtweekendutil.h"

#include "HittableList.h"
#include "sphere.h"
#include "Camera.h"
using namespace Vector3Namespace;

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
    hit_record record;

    if (world.hit(r, 0.001, infinity, record)) {
        Point3 target = record.p + randomInHemisphere(record.normal);
        return 0.5 * ray_color(Ray(record.p, target - record.p), world, depth - 1);
    }

    Vec3 unit_direction = Vector3Namespace::unit_vector(r.direction());
    auto t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
}

int main() {

    // Image
    const auto kAspectRatio = 16.0 / 9.0;
    const int kImageWidth = 900;
    const int kImageHeight = static_cast<int> (kImageWidth / kAspectRatio);
    const int samplesPerPixel = 100;
    const int maxDepth = 30;

    //world
    HittableList world;
    world.add(make_shared<Sphere>(Point3(0, 0, -1), 0.5));
    world.add(make_shared<Sphere>(Point3(0, -100.5, -1), 100));

    // Camera
    Camera cam;

    // Render

    std::cout << "P3\n" << kImageWidth << ' ' << kImageHeight << "\n255\n";

    for (int j = kImageHeight - 1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < kImageWidth; ++i) {
            Color pixel_color(0, 0, 0);
            for (int s = 0; s < samplesPerPixel; ++s) {
                auto u = (i + random_double()) / (kImageWidth - 1);
                auto v = (j + random_double()) / (kImageHeight - 1);
                Ray r = cam.getRay(u, v);
                pixel_color += ray_color(r, world, maxDepth);
            }
            ColorUtil::WriteColor(std::cout, pixel_color, samplesPerPixel);
        }
    }
    std::cerr << "\nDone.\n";
}