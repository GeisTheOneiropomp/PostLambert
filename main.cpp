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
#include "ImageTexture.h"
#include "CheckerTexture.h"
#include "NoiseTexture.h"

using namespace rtweekend_math;

int main() {

    // Image
    auto kAspectRatio = 16.0 / 9.0;
    int kImageWidth = 1600;
    int kImageHeight = static_cast<int> (kImageWidth / kAspectRatio);
    int samplesPerPixel = 10;
    int maxDepth = 30;

    //world
    auto R = cos(pi / 4);

    auto world = earth();
    Point3 lookfrom(13, 2, 3);
    Point3 lookat(0, 0, 0);
    Vec3 vup(0, 1, 0);
    auto dist_to_focus = 10;
    auto aperture = 0.0;
    double fieldOfView = 40;
    Color background(0, 0, 0);

    switch (0) {
    case 1:
        world = RandomScene();
        lookfrom = Point3(13, 2, 3);
        background = Color(0.70, 0.80, 1.00);
        lookat = Point3(0, 0, 0);
        fieldOfView = 20.0;
        aperture = 0.1;
        break;
    case 2:
        world = two_spheres();
        background = Color(0.70, 0.80, 1.00);
        lookfrom = Point3(13, 2, 3);
        lookat = Point3(0, 0, 0);
        fieldOfView = 20.0;
        break;
    case 3:
        world = earth();
        background = Color(0.70, 0.80, 1.00);
        lookfrom = Point3(13, 2, 3);
        lookat = Point3(0, 0, 0);
        fieldOfView = 20.0;
        break;
    case 4:
        world = two_perlin_spheres();
        background = Color(0.90, 0.60, 0.60);
        lookfrom = Point3(13, 2, 3);
        lookat = Point3(0, 0, 0);
        fieldOfView = 20.0;
        break;
    case 5:
        world = simple_light();
        samplesPerPixel = 400;
        background = Color(0, 0, 0);
        lookfrom = Point3(26, 3, 6);
        lookat = Point3(0, 2, 0);
        fieldOfView = 20.0;
        break;
    default:
    case 6:
        world = CornellBox();
        kAspectRatio = 1.0;
        kImageWidth = 600;
        samplesPerPixel = 200;
        background = Color(0, 0, 0);
        lookfrom = Point3(278, 278, -800);
        lookat = Point3(278, 278, 0);
        fieldOfView = 40.0;
        break;
    }

    Camera cam(lookfrom, lookat, vup, fieldOfView, kAspectRatio, aperture, dist_to_focus, 0.0, 1.0);
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
                pixel_color += RayColorWithBackground(r, background, world, maxDepth);
            }
            ColorUtil::WriteColor(std::cout, pixel_color, samplesPerPixel);
        }
    }
    std::cerr << "\nDone.\n";
}