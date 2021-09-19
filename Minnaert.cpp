#include "Minnaert.h"
#include "SolidColor.h"
#include "Vec3Util.h"
#include "Hittable.h"
#include <math.h>

using std::make_shared;
Minnaert::Minnaert(const Color& a, const double exponent)
	: albedo(make_shared<SolidColor>(a)), exponent(exponent)
{
}

Minnaert::Minnaert(shared_ptr<Texture> a, const double exponent)
	:albedo(a), exponent(exponent)
{
}

bool Minnaert::scatter(const Ray& r_in, const HitRecord& record, Color& attenuation, Ray& scattered) const
{
    Vec3 unitNormal = UnitVector(record.normal);
    auto scatter_direction = UnitVector(unitNormal + RandomUnitVector());
    if (scatter_direction.isNearZero())
        scatter_direction = unitNormal;

    scattered = Ray(record.point, scatter_direction, r_in.time());
    auto cosine = Dot(record.normal, scatter_direction);
    auto mu = Dot(record.normal, UnitVector(-1 * r_in.direction()));
    auto mu_naught = Dot(record.normal, UnitVector(scatter_direction));
    attenuation = albedo->value(record.u_coord, record.v_coord, record.point) * (pow(mu, exponent) + pow(mu_naught, exponent - 1));
    return true;
}
