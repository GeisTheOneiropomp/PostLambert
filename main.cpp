#include <iostream>
#include "ColorUtil.h"
#include "Ray.h"
#include "vec3.h"
#include "Vec3Util.h"

using namespace Vector3Namespace;

Color ray_color(const Ray& r) {
    Vec3 unit_direction = Vector3Namespace::unit_vector(r.direction_);
    auto t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
}

int main() {

    // Image
    const auto kAspectRatio = 16.0 / 9.0;
    const int kImageWidth = 900;
    const int kImageHeight = static_cast<int> (kImageWidth / kAspectRatio);

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
            auto u = double(i) / kImageWidth - 1;
            auto v = double(j) / kImageHeight - 1;
            Ray r(origin, lowerLeftCorner + u * horizontal + v * vertical - origin);
            Color pixel_color = ray_color(r);
            ColorUtil::WriteColor(std::cout, pixel_color);
        }
    }
    std::cerr << "\nDone.\n";
}