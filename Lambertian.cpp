#include "Lambertian.h"
#include "Hittable.h"
#include "Vec3Util.h"

Lambertian::Lambertian(const Color& a) : albedo(a)
{
}

bool Lambertian::scatter(const Ray& r_in, const HitRecord& record, Color& attenuation, Ray& scattered) const
{
    Vec3 unitNormal = UnitVector(record.normal);
    auto scatter_direction = UnitVector(unitNormal + RandomUnitVector());
    if (scatter_direction.nearZero())
        scatter_direction = unitNormal;

    scattered = Ray(record.point, scatter_direction, r_in.time());
    auto cosine = Dot(record.normal, scatter_direction);
    attenuation = cosine * albedo;
    return true;
}
