#include <iostream>
#include "ColorUtil.h"
#include "Ray.h"
#include "vec3.h"
#include "Vec3Util.h"
#include "rtweekend.h"

#include "HittableList.h"
#include "sphere.h"
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

Color ray_color(const Ray& r, const Hittable& world) {
    hit_record record;
    if (world.hit(r, 0, infinity, record)) {
        return 0.5 * (record.normal + Color(1, 1, 1));
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

    //world
    HittableList world;
    world.add(make_shared<Sphere>(Point3(0, 0, -1), 0.5));
    world.add(make_shared<Sphere>(Point3(0, -100.5, -1), 100));

    // Camera
    auto kViewportHeight = 2.0;
    auto kViewportWidth = kAspectRatio * kViewportHeight;
    auto focalLength = 1.0;

    auto origin = Point3(0, 0, 0);
    auto horizontal = Vec3(kViewportWidth, 0, 0);
    auto vertical = Vec3(0, kViewportHeight, 0);
    auto lowerLeftCorner = origin - horizontal / 2 - vertical / 2 - Vec3(0, 0, focalLength);
    // Render

    std::cout << "P3\n" << kImageWidth << ' ' << kImageHeight << "\n255\n";

    for (int j = kImageHeight - 1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < kImageWidth; ++i) {
            auto u = double(i) / (kImageWidth - 1);
            auto v = double(j) / (kImageHeight - 1);
            Ray r(origin, lowerLeftCorner + u * horizontal + v * vertical - origin);
            Color pixel_color = ray_color(r, world);
            ColorUtil::WriteColor(std::cout, pixel_color);
        }
    }
    std::cerr << "\nDone.\n";
}