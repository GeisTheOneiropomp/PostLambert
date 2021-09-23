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
#include "math.h"
#include "Skybox.h"

using namespace rtweekend_math;

int main() {

    // Image
    auto kAspectRatio = 16.0 / 9.0;
    int kImageWidth = 1600;
    int kImageHeight = static_cast<int> (kImageWidth / kAspectRatio);
    int samplesPerPixel = 100;
    int maxDepth = 30;

    //world
    auto R = cos(pi / 4);

    auto world = earth();
    auto skybox = new Skybox("img\\skyboxes\\tsuruta\\");
    Point3 lookfrom(13, 2, 3);
    Point3 lookat(0, 0, 0);
    Vec3 vup(0, 1, 0);
    auto distToFocus = 10;
    auto aperture = 0.0;
    double fieldOfView = 40;
    double tilt0 = 0;
    double shift0 = 0;
    double tilt1 = 1;
    double shift1 = 1;
    Color background(0, 0, 0);

    switch (0) {
    default:
    case 1:
        world = RandomScene();    
        samplesPerPixel = 100;
        lookfrom = Point3(13, 2, 3);
        background = Color(0.70, 0.80, 1.00);
        lookat = Point3(0, 0, 0);
        fieldOfView = 60;
        //aperture = 0.1;
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
    case 6:
        world = CornellBox();
        kAspectRatio = 1.0;
        kImageWidth = 600;
        samplesPerPixel = 100;
        background = Color(0, 0, 0);
        lookfrom = Point3(278, 278, -800);
        lookat = Point3(278, 278, 0);
        fieldOfView = 40.0;
        break;
    case 7:
        world = CornellSmoke();
        kAspectRatio = 1.0;
        kImageWidth = 700;
        samplesPerPixel = 200;
        lookfrom = Point3(278, 278, -800);
        lookat = Point3(278, 278, 0);
        fieldOfView = 40.0;
        break; 
    case 8:
        world = MoonScene();
        kAspectRatio = 2.0;
        lookfrom = Point3(3.25, .5, 10);
        samplesPerPixel = 2000;
        background = Color(0.3, 0.3, 0.3);
        lookat = Point3(0, 0, 0);
        fieldOfView = 20.0;
        aperture = 0.1;
        break;
    }

    Camera cam(lookfrom, lookat, vup, fieldOfView, kAspectRatio, aperture, distToFocus, 0.0, 1.0, tilt0, shift0, shift1, tilt1);
    // Render

    std::cout << "P3\n" << kImageWidth << ' ' << kImageHeight << "\n255\n";

    for (int j = kImageHeight - 1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < kImageWidth; ++i) {
            Color normal_pixel_color(0, 0, 0);
            for (int s = 0; s < samplesPerPixel; ++s) {
                auto u = (i + RandomDouble()) / (kImageWidth - 1);
                auto v = (j + RandomDouble()) / (kImageHeight - 1);

                if (RandomDouble(0, 1) < .9) {
                    Ray r = cam.getRay(u, v);
                    normal_pixel_color += cam.vignetteFactor(u,v)* RayColorWithBackground(r, skybox, world, maxDepth);
                }
                else {
                    MonochromaticRay mr = cam.getDiffractionRay(u, v, RandomDouble(380.00, 750.00));
                    auto val = cam.vignetteFactor(u,v) * DiffractionRayColorWithBackground(mr, skybox, world, maxDepth);
                    normal_pixel_color += val;
                }
            }
            
            ColorUtil::WriteColor(std::cout, normal_pixel_color, samplesPerPixel);
        }
    }
    std::cerr << "\nDone.\n";
}