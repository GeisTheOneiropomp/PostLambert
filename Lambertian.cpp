#include "Lambertian.h"
#include "Hittable.h"
Lambertian::Lambertian(const Color& a) : albedo(a)
{
}
bool Lambertian::scatter(const Ray& r_in, const hitRecord& record, Color& attenuation, Ray& scattered) const
{
    auto scatter_direction = record.normal + RandomUnitVector();

    if (scatter_direction.nearZero())
        scatter_direction = record.normal;

    scattered = Ray(record.point, scatter_direction);
    attenuation = albedo;
    return true;
}
