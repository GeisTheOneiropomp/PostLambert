#include <iostream>
#include <fstream>

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
#include "LunarLambert.h"
#include "Metal.h"
#include "Dielectric.h"
#include "SceneUtil.h"
#include "RayColorUtil.h"
#include "ImageTexture.h"
#include "math.h"
#include "Skybox.h"
#include "FileResources.h"
#include "Hapke.h"
#include "Minnaert.h"
#include "LommelSeeliger.h"
#include "Config.h"

using namespace rt_math;

int main() {

    //world
    auto R = cos(pi / 4);

    auto skybox = new Skybox(SKYBOX_FILE);
    Point3 lookfrom(13, 2, 3);
    Point3 lookat(0, 0, 0);
    Vec3 vup(0, 1, 0);
    auto distToFocus = 10;
    auto aperture = 0.0;
    double fieldOfView = 100;
    Color background(0, 0, 0);
    HittableList world;
    switch (ScenePath) {
    case SCENEPATH::BALLSCENE :
        world = RandomScene();    
        lookfrom = Point3(13, 2, 3);
        background = Color(0.70, 0.80, 1.00);
        lookat = Point3(0, 0, 0);
        fieldOfView = 30;
        aperture = 0.0;
        break;
    default:
    case SCENEPATH::MOON :
        auto moonTexture = make_shared<ImageTexture>(MOON_FILE);
        shared_ptr<Material> moonMaterial = make_shared<Hapke>(moonTexture, .5);
        world = MoonScene(moonMaterial);
        lookfrom = Point3(7, 0, 0);
        lookat = Point3(0, 0, 0);
        fieldOfView = 30.0;
        break;
    }

    Camera cam(lookfrom, lookat, vup, fieldOfView, AspectRatio, aperture, distToFocus);
    // Render

    std::ofstream outfile;
    outfile.open(OUTPUT);

    outfile << "P3\n" << ImageWidth << ' ' << ImageHeight << "\n255\n";

    for (int j = ImageHeight - 1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < ImageWidth; ++i) {
            Color normal_pixel_color(0, 0, 0);
            for (int s = 0; s < SamplesPerPixel; ++s) {
                auto u = (i + RandomDouble()) /  (double (ImageWidth - 1.0));
                auto v = (j + RandomDouble()) /  (double (ImageHeight - 1.0));
                    Ray r = cam.getRay(u, v);
                    normal_pixel_color +=  RayColorWithBackground(r, skybox, world, MaxDepth);               
            }
            ColorUtil::WriteColor(outfile, normal_pixel_color, SamplesPerPixel);
        }
    }
    std::cerr << "\nDone.\n";
}