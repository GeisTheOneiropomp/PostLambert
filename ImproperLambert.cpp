#include "ImproperLambert.h"
#include "Hittable.h"
#include "Vec3Util.h"

ImproperLambert::ImproperLambert(const Color& a) : albedo(a)
{
}

bool ImproperLambert::scatter(const Ray& r_in, const hitRecord& record, Color& attenuation, Ray& scattered) const
{
    auto scatter_direction = record.normal + RandomUnitVector();
    if (scatter_direction.nearZero())
        scatter_direction = record.normal;

    scattered = Ray(record.point, scatter_direction);
    attenuation =  albedo;
    return true;
}