#include "LunarLambert.h"
#include "SolidColor.h"
#include "Vec3Util.h"
#include "Hittable.h"

using std::make_shared;

LunarLambert::LunarLambert(const Color& a, const double a_coefficient, const double b_coefficient) 
    : albedo(make_shared<SolidColor>(a)), a_coefficient(a_coefficient), b_coefficient(b_coefficient)
{
}

LunarLambert::LunarLambert(shared_ptr<Texture> a, const double a_coefficient, const double b_coefficient)
    : albedo(a), a_coefficient(a_coefficient), b_coefficient(b_coefficient)
{
}

bool LunarLambert::scatter(const Ray& r_in, const HitRecord& record, Color& attenuation, Ray& scattered) const
{
    Vec3 unitNormal = UnitVector(record.normal);
    auto scatter_direction = UnitVector(unitNormal + RandomUnitVector());
    if (scatter_direction.isNearZero())
        scatter_direction = unitNormal;

    scattered = Ray(record.point, scatter_direction, r_in.time());
    auto cosine = Dot(record.normal, scatter_direction);
    auto mu = Dot(record.normal, UnitVector(-1 * r_in.direction()));
    auto mu_naught = Dot(record.normal, UnitVector(scatter_direction));
    auto a_term = cosine * albedo->value(record.u_coord, record.v_coord, record.point);
    auto b_term = albedo->value(record.u_coord, record.v_coord, record.point) / (4 * mu * mu_naught);
    attenuation = (a_term * a_coefficient) + (b_term * b_coefficient);
    return true;
}
