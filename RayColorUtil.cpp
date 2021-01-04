#include "RayColorUtil.h"


Color RayColor(const Ray& ray, const Hittable& world, int depth) {

    if (depth == 0) {
        return Color(0, 0, 0);
    }
    HitRecord record;

    if (world.Hit(ray, 0.001, rtweekend_math::infinity, record)) {
        Ray scattered;
        Color attenuation;
        if (record.material_pointer->scatter(ray, record, attenuation, scattered)) {
            return attenuation * RayColor(scattered, world, depth - 1);
        }
        return Color(0, 0, 0);
    }

    Vec3 unit_direction = UnitVector(ray.direction());
    auto t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
}