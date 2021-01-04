#include "Lambertian.h"
#include "Hittable.h"
#include "Vec3Util.h"

Lambertian::Lambertian(const Color& a) : albedo(a)
{
}

bool Lambertian::scatter(const Ray& r_in, const hitRecord& record, Color& attenuation, Ray& scattered) const
{
    Vec3 unitNormal = unit_vector(record.normal);
    auto scatter_direction = unit_vector(unitNormal + RandomUnitVector());
    if (scatter_direction.nearZero())
        scatter_direction = unitNormal;

    scattered = Ray(record.point, scatter_direction, r_in.time());
    auto cosine = dot(record.normal, scatter_direction);
    attenuation = cosine * albedo;
    return true;
}
