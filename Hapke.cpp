#include "Hapke.h"
#include "Hittable.h"
#include "SolidColor.h"
#include "PhaseFunctionsUtils.h"
#include "Vec3Util.h"

using std::make_shared;

Hapke::Hapke(const Color& a, const double theta) : albedo(make_shared<SolidColor>(a)), theta(theta)
{
}

Hapke::Hapke(shared_ptr<Texture> a, const double theta) : albedo(a), theta(theta)
{
}

bool Hapke::scatter(const Ray& r_in, const HitRecord& record, Color& attenuation, Ray& scattered) const
{
    auto scatter_direction = record.normal + RandomUnitVector();

    if (scatter_direction.nearZero())
        scatter_direction = record.normal;

    auto mu = Dot(record.normal, UnitVector(-1 * r_in.direction()));
    auto mu_naught = Dot(record.normal, UnitVector(scatter_direction));
    auto factor = mu_naught / (4 * mu * mu_naught);
    scattered = Ray(record.point, scatter_direction, r_in.time());
    auto pointAlbedo = albedo->value(record.u_coord, record.v_coord, record.point);
    attenuation = albedo->value(record.u_coord, record.v_coord, record.point) * 
        (factor * (1 + (HFunction(mu_naught, pointAlbedo) * HFunction(mu, pointAlbedo)) -1));
    return true;
}

double Hapke::HFunction(const double input, const Color albedo) const {
    auto numerator = 1 + (2 * input);
    auto denominator = 1 + (2 * input) * (sqrt(1 - (albedo.Length() / 3)));
    return numerator / denominator;
}

double Hapke::ScatterMode1(const Ray& r_in, const HitRecord& record, Color& attenuation, Ray& scattered) const {
   
    // assume scattering is isotropic right now.
    auto scatter_direction = record.normal + RandomUnitVector();

    if (scatter_direction.nearZero())
        scatter_direction = record.normal;

    auto i = acos(Dot(r_in.direction() / r_in.direction().Length(), record.normal / record.normal.Length()));
    auto e = acos(Dot(scatter_direction / scatter_direction.Length(), record.normal / record.normal.Length()));
    auto psi = findPsi(r_in.direction(), scatter_direction, record.normal);
    auto shadow = HapkeShadowing(theta, i, e, psi);

    scattered = Ray(record.point, scatter_direction, r_in.time());
    auto pointAlbedo = albedo->value(record.u_coord, record.v_coord, record.point);
    return true;
}