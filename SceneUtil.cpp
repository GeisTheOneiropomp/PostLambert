#include "SceneUtil.h"
#include "Lambertian.h"
#include "Sphere.h"
#include "Metal.h"
#include "Dielectric.h"
#include "ImproperLambert.h"
#include "LommelSeeliger.h"
#include "MovingSphere.h"
#include "CheckerTexture.h"
#include "NoiseTexture.h"
#include "ImageTexture.h"
#include "DiffuseLight.h"
#include "XYRectangle.h"
#include "YZRectangle.h"
#include "XZRectangle.h"
#include "Box.h"
#include "Translate.h"
#include "YRotate.h"
#include "HittableList.h"
#include "ConstantMedium.h"
#include "BVHNode.h"
#include "LunarLambert.h"
#include "Minnaert.h"
#include "Hapke.h"

using namespace rt_math;

HittableList CornellBox() {
    HittableList objects;

    auto red = make_shared<ImproperLambert>(Color(.65, .05, .05));
    auto white = make_shared<ImproperLambert>(Color(.73, .73, .73));
    auto green = make_shared<ImproperLambert>(Color(.12, .45, .15));
    auto light = make_shared<DiffuseLight>(Color(15, 15, 15));

    objects.add(make_shared<YZRectangle>(0, 555, 0, 555, 555, green));
    objects.add(make_shared<YZRectangle>(0, 555, 0, 555, 0, red));
    objects.add(make_shared<XZRectangle>(213, 343, 227, 332, 554, light));
    objects.add(make_shared<XZRectangle>(0, 555, 0, 555, 0, white));
    objects.add(make_shared<XZRectangle>(0, 555, 0, 555, 555, white));
    objects.add(make_shared<XYRectangle>(0, 555, 0, 555, 555, white));

    auto pertext = make_shared<NoiseTexture>(10);
    objects.add(make_shared<Box>(Point3(130, 0, 65), Point3(295, 165, 230), white));
    //box1 = make_shared<YRotate>(box1, 15);
    //box1 = make_shared<Translate>(box1, Vec3(265, 0, 295));

    objects.add(make_shared<Box>(Point3(265, 0, 295), Point3(430, 330, 460), white));
    //box2 = make_shared<YRotate>(box2, -18);
    //box2 = make_shared<Translate>(box2, Vec3(130, 0, 65));
    return objects;
}

HittableList CornellSmoke()
{
        HittableList objects;

        auto red = make_shared<Lambertian>(Color(.65, .05, .05));
        auto white = make_shared<Lambertian>(Color(.73, .73, .73));
        auto green = make_shared<Lambertian>(Color(.12, .45, .15));
        auto light = make_shared<DiffuseLight>(Color(7, 7, 7));

        objects.add(make_shared<YZRectangle>(0, 555, 0, 555, 555, green));
        objects.add(make_shared<YZRectangle>(0, 555, 0, 555, 0, red));
        objects.add(make_shared<XZRectangle>(113, 443, 127, 432, 554, light));
        objects.add(make_shared<XZRectangle>(0, 555, 0, 555, 555, white));
        objects.add(make_shared<XZRectangle>(0, 555, 0, 555, 0, white));
        objects.add(make_shared<XYRectangle>(0, 555, 0, 555, 555, white));

        shared_ptr<Hittable> box1 = make_shared<Box>(Point3(0, 0, 0), Point3(165, 330, 165), white);
        box1 = make_shared<YRotate>(box1, 15);
        box1 = make_shared<Translate>(box1, Vec3(265, 0, 295));

        shared_ptr<Hittable> box2 = make_shared<Box>(Point3(0, 0, 0), Point3(165, 165, 165), white);
        box2 = make_shared<YRotate>(box2, -18);
        box2 = make_shared<Translate>(box2, Vec3(130, 0, 65));

        objects.add(make_shared<ConstantMedium>(box1, 0.01, Color(0, 0, 0)));
        objects.add(make_shared<ConstantMedium>(box2, 0.01, Color(1, 1, 1)));

        return objects;
}

HittableList simple_light() {
    HittableList objects;

    auto pertext = make_shared<NoiseTexture>(4);
    objects.add(make_shared<Sphere>(Point3(0, -1000, 0), 1000, make_shared<Lambertian>(pertext)));
    objects.add(make_shared<Sphere>(Point3(0, 2, 0), 2, make_shared<Lambertian>(pertext)));

    auto difflight = make_shared<DiffuseLight>(Color(4, 4, 4));
    objects.add(make_shared<XYRectangle>(3, 5, 1, 3, -2, difflight));

    return objects;
}

HittableList earth() {
    auto earth_texture = make_shared<ImageTexture>("img\\earthmap.jpg");
    auto earth_surface = make_shared<Lambertian>(earth_texture);
    auto globe = make_shared<Sphere>(Point3(0, 0, 0), 2, earth_surface);
    return HittableList(globe);
}

HittableList two_spheres() {
    HittableList objects;
    auto checker = make_shared<CheckerTexture>(Color(0.2, 0.3, 0.1), Color(0.9, 0.9, 0.9));
    objects.add(make_shared<Sphere>(Point3(0, -10, 0), 10, make_shared<Lambertian>(checker)));
    objects.add(make_shared<Sphere>(Point3(0, 10, 0), 10, make_shared<Lambertian>(checker)));
    return objects;
}

HittableList two_perlin_spheres() {
    HittableList objects;

    auto pertext = make_shared<NoiseTexture>(10);
    objects.add(make_shared<Sphere>(Point3(0, -1000, 0), 1000, make_shared<Lambertian>(pertext)));
    objects.add(make_shared<Sphere>(Point3(0, 2, 0), 2, make_shared<Lambertian>(pertext)));

    return objects;
}

HittableList RandomScene() {
    HittableList world;

    // auto checker = make_shared<CheckerTexture>(Color(0.2, 0.3, 0.1), Color(0.9, 0.9, 0.9));
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

HittableList final_scene() {
    HittableList boxes1;
    auto ground = make_shared<Lambertian>(Color(0.48, 0.83, 0.53));

    const int boxes_per_side = 20;
    for (int i = 0; i < boxes_per_side; i++) {
        for (int j = 0; j < boxes_per_side; j++) {
            auto w = 100.0;
            auto x0 = -1000.0 + i * w;
            auto z0 = -1000.0 + j * w;
            auto y0 = 0.0;
            auto x1 = x0 + w;
            auto y1 = RandomDouble(1, 101);
            auto z1 = z0 + w;

            boxes1.add(make_shared<Box>(Point3(x0, y0, z0), Point3(x1, y1, z1), ground));
        }
    }

    HittableList objects;

    objects.add(make_shared<BVHNode>(boxes1, 0, 1));

    auto light = make_shared<DiffuseLight>(Color(7, 7, 7));
    objects.add(make_shared<XZRectangle>(123, 423, 147, 412, 554, light));

    auto center1 = Point3(400, 400, 200);
    auto center2 = center1 + Vec3(30, 0, 0);
    auto moving_sphere_material = make_shared<Lambertian>(Color(0.7, 0.3, 0.1));
    objects.add(make_shared<MovingSphere>(center1, center2, 0, 1, 50, moving_sphere_material));

    objects.add(make_shared<Sphere>(Point3(260, 150, 45), 50, make_shared<Dielectric>(1.5)));
    objects.add(make_shared<Sphere>(
        Point3(0, 150, 145), 50, make_shared<Metal>(Color(0.8, 0.8, 0.9), 1.0)
        ));

    auto boundary = make_shared<Sphere>(Point3(360, 150, 145), 70, make_shared<Dielectric>(1.5));
    objects.add(boundary);
    objects.add(make_shared<ConstantMedium>(boundary, 0.2, Color(0.2, 0.4, 0.9)));
    boundary = make_shared<Sphere>(Point3(0, 0, 0), 5000, make_shared<Dielectric>(1.5));
    objects.add(make_shared<ConstantMedium>(boundary, .0001, Color(1, 1, 1)));

    auto emat = make_shared<Lambertian>(make_shared<ImageTexture>("img\\earthmap.jpg"));
    objects.add(make_shared<Sphere>(Point3(400, 200, 400), 100, emat));
    auto pertext = make_shared<NoiseTexture>(0.1);
    objects.add(make_shared<Sphere>(Point3(220, 280, 300), 80, make_shared<Lambertian>(pertext)));

    HittableList boxes2;
    auto white = make_shared<Lambertian>(Color(.73, .73, .73));
    int ns = 1000;
    for (int j = 0; j < ns; j++) {
        boxes2.add(make_shared<Sphere>(random(0, 165), 10, white));
    }

    objects.add(make_shared<Translate>(
        make_shared<YRotate>(
            make_shared<BVHNode>(boxes2, 0.0, 1.0), 15),
        Vec3(-100, 270, 395)
        )
    );

    return objects;
}

HittableList MoonScene() {
    HittableList world;

    auto moon_texture = make_shared<ImageTexture>("img\\moon.jpg");
    auto moon_surface = make_shared<Hapke>(moon_texture, 1);
    auto moon = make_shared<Sphere>(Point3(0, 0, 0), 1.75, moon_surface);
    world.add(moon);

    return world;
}
