#include "RayColorUtil.h"
#include "Ray.h"
#include "Hittable.h"
#include "RTWeekendUtil.h"

Color RayColor(const Ray& r, const Hittable& world, int depth) {

    if (depth == 0) {
        return Color(0, 0, 0);
    }
    hitRecord record;

    if (world.hit(r, 0.001, rtweekend_math::infinity, record)) {
        Ray scattered;
        Color attenuation;
        if (record.materialPointer->scatter(r, record, attenuation, scattered)) {
            return attenuation * RayColor(scattered, world, depth - 1);
        }
        return Color(0, 0, 0);
    }

    Vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
}