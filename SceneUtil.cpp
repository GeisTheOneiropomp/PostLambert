#include "SceneUtil.h"
#include "Lambertian.h"
#include "Sphere.h"
#include "Metal.h"
#include "Dielectric.h"
#include "ImproperLambert.h"
#include "LommelSeeliger.h"
#include "MovingSphere.h"
#include "ImageTexture.h"
#include "DiffuseLight.h"
#include "HittableList.h"
#include "LunarLambert.h"
#include "Minnaert.h"
#include "Hapke.h"

using namespace rt_math;

HittableList RandomScene() {
    HittableList world;

    // world.add(make_shared<Sphere>(Point3(0, -1000, 0), 1000, make_shared<Lambertian>(checker)));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = RandomDouble();
            Point3 center(a + 0.9 * RandomDouble(), 0.2 +RandomInt(-3,3), b + 0.9 * RandomDouble());

            if ((center - Point3(4, 0.2, 0)).Length() > 0.9) {
                shared_ptr<Material> sphere_material;

                //if (choose_mat < .7) {
                //    // diffuse
                //    auto albedo = random() * random();
                //    sphere_material = make_shared<Hapke>(albedo, 1);
                //    auto center2 = center + Vec3(0, RandomDouble(0, 0.5), 0);
                //    world.add(make_shared<Sphere>(center, 0.2, sphere_material));
                //}

                //if (choose_mat < 0.8) {
                //    // diffuse
                //    auto albedo = random() * random();
                //    sphere_material = make_shared<Hapke>(albedo, 1);
                //    world.add(make_shared<Sphere>(center, 0.2, sphere_material));
                //}
                if (choose_mat < 0.1) {
                    // metal
                    auto albedo = random(0.5, 1);
                    auto fuzz = RandomDouble(0, 0.5);
                    sphere_material = make_shared<Metal>(albedo, fuzz);
                    world.add(make_shared<Sphere>(center, 0.2 + RandomDouble(-.1, .4), sphere_material));
                }
                else if (choose_mat < 0.2) {
                    // glass
                    sphere_material = make_shared<Dielectric>(1.5);
                    world.add(make_shared<Sphere>(center, 0.2 + RandomDouble(-.1, .4), sphere_material));
                }
            }
        }
    }

    auto material1 = make_shared<Dielectric>(1.5);
    world.add(make_shared<Sphere>(Point3(0, 0, 0), 1.0, material1));

    //auto material2 = make_shared<Lambertian>(Color(0.4, 0.2, 0.1));
    //world.add(make_shared<Sphere>(Point3(-4, 1, 0), 1.0, material2));

    //auto material3 = make_shared<Metal>(Color(0.7, 0.6, 0.5), 0.0);
    //world.add(make_shared<Sphere>(Point3(4, 1, 0), 1.0, material3));

    return world;
}

HittableList MoonScene(string fileName) {
    HittableList world;
    auto moon_texture = make_shared<ImageTexture>(fileName);
    auto moon_surface = make_shared<Hapke>(moon_texture, 1);
    auto moon = make_shared<Sphere>(Point3(0, 0, 0), 1.75, moon_surface);
    world.add(moon);
    return world;
}
