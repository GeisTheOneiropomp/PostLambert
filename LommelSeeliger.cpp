#include "LommelSeeliger.h"
#include "Vec3Util.h"
#include "Hittable.h"
#include "SolidColor.h"

using std::make_shared;

LommelSeeliger::LommelSeeliger(const Color& a) : albedo(make_shared<SolidColor>(a))
{
}

LommelSeeliger::LommelSeeliger(std::shared_ptr<Texture> a) : albedo(a)
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
    attenuation = albedo->value(record.u_coord, record.v_coord, record.point) / 4;
    attenuation = albedo->value(record.u_coord, record.v_coord, record.point) / (mu * mu_naught);
    return true;
}