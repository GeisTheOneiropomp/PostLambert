#include "LommelSeeliger.h"
#include "Vec3Util.h"
#include "Hittable.h"

LommelSeeliger::LommelSeeliger(const Color& a) : albedo(a)
{
}

bool LommelSeeliger::scatter(const Ray& r_in, const HitRecord& record, Color& attenuation, Ray& scattered) const
{
    auto scatter_direction = record.normal + RandomUnitVector();

    if (scatter_direction.nearZero())
        scatter_direction = record.normal;

    auto mu = Dot(record.normal, UnitVector(-1 * r_in.direction()));
    auto mu_naught = Dot(record.normal, UnitVector(scatter_direction));
    scattered = Ray(record.point, scatter_direction, r_in.time());
    attenuation = albedo / 4;
    attenuation = albedo / (mu * mu_naught);
    return true;
}