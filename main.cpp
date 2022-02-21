#include <iostream>
#include "ColorUtil.h"
#include "Ray.h"
#include "vec3.h"
#include "Vec3Util.h"
#include "rtutil.h"
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
#include "math.h"
#include "Skybox.h"
#include "FileResources.h"
#include "Hapke.h"

using namespace rt_math;

int main() {

    // Image
    auto kAspectRatio = 16.0 / 9.0;
    int kImageWidth = 1600;
    int kImageHeight = static_cast<int> (kImageWidth / kAspectRatio);
    int samplesPerPixel = 100;
    int maxDepth = 30;

    //world
    auto R = cos(pi / 4);

    auto skybox = new Skybox(NIGHTSKY_FILE);
    Point3 lookfrom(13, 2, 3);
    Point3 lookat(0, 0, 0);
    Vec3 vup(0, 1, 0);
    auto distToFocus = 10;
    auto aperture = 0.0;
    double fieldOfView = 100;
    Color background(0, 0, 0);
    HittableList world;
    switch (0) {
    case 1:
        world = RandomScene();    
        samplesPerPixel = 100;
        lookfrom = Point3(3, 2, 3);
        background = Color(0.70, 0.80, 1.00);
        lookat = Point3(0, 0, 0);
        fieldOfView = 100;
        aperture = 0.1;
        break;
    default:
    case 2:
        auto moonTexture = make_shared<ImageTexture>(MOON_FILE);
        shared_ptr<Material> moonMaterial = make_shared<Hapke>(moonTexture, 1);
        world = MoonScene(moonMaterial);
        kAspectRatio = 2.0;
        lookfrom = Point3(0, 1, .2);
        samplesPerPixel = 20;
        lookat = Point3(0, 0, 0);
        fieldOfView = 30.0;
        aperture = 0.0;
        break;
    }

    Camera cam(lookfrom, lookat, vup, fieldOfView, kAspectRatio, aperture, distToFocus);
    // Render

    std::cout << "P3\n" << kImageWidth << ' ' << kImageHeight << "\n255\n";

    for (int j = kImageHeight - 1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < kImageWidth; ++i) {
            Color normal_pixel_color(0, 0, 0);
            for (int s = 0; s < samplesPerPixel; ++s) {
                auto u = (i + RandomDouble()) /  (double (kImageWidth - 1.0));
                auto v = (j + RandomDouble()) /  (double (kImageHeight - 1.0));
                    Ray r = cam.getRay(u, v);
                    normal_pixel_color +=  RayColorWithBackground(r, skybox, world, maxDepth);               
            }
            ColorUtil::WriteColor(std::cout, normal_pixel_color, samplesPerPixel);
        }
    }
    std::cerr << "\nDone.\n";
}