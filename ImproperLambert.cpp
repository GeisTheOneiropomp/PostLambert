#include "ImproperLambert.h"
#include "Hittable.h"
#include "Vec3Util.h"

ImproperLambert::ImproperLambert(const Color& a) : albedo(a)
{
}

bool ImproperLambert::scatter(const Ray& r_in, const HitRecord& record, Color& attenuation, Ray& scattered) const
{
    auto scatter_direction = record.normal + RandomUnitVector();
    if (scatter_direction.isNearZero())
        scatter_direction = record.normal;

    scattered = Ray(record.point, scatter_direction, r_in.time());
    attenuation =  albedo;
    return true;
}