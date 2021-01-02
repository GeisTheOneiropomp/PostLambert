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
#include "SceneUtil.h"
#include "RayColorUtil.h"

using namespace rtweekend_math;

int main() {

    // Image
    const auto kAspectRatio = 16.0 / 9.0;
    const int kImageWidth = 1600;
    const int kImageHeight = static_cast<int> (kImageWidth / kAspectRatio);
    const int samplesPerPixel = 500;
    const int maxDepth = 30;

    //world
    auto R = cos(pi / 4);

    auto world = RandomScene();

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
                pixel_color += RayColor(r, world, maxDepth);
            }
            ColorUtil::WriteColor(std::cout, pixel_color, samplesPerPixel);
        }
    }
    std::cerr << "\nDone.\n";
}