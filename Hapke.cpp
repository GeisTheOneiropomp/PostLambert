#include "Hapke.h"
#include "Hittable.h"
#include "SolidColor.h"
#include "PhaseFunctionsUtils.h"
#include "Vec3Util.h"
#include "math.h"
using std::make_shared;

Hapke::Hapke(const Color& a, const double theta) : albedo(make_shared<SolidColor>(a)), theta(theta)
{
}

Hapke::Hapke(shared_ptr<Texture> a, const double theta) : albedo(a), theta(theta)
{
}

bool Hapke::scatter(const Ray& r_in, const HitRecord& record, Color& attenuation, Ray& scattered) const
{
    // assume scattering is isotropic right now.
    Vec3 unitNormal = UnitVector(record.normal);
    auto scatter_direction = UnitVector(unitNormal + RandomUnitVector());
    if (scatter_direction.nearZero()) {
            scatter_direction = record.normal;
    }
    auto mu = Dot(record.normal, UnitVector(-1 * r_in.direction()));
    auto mu_naught = Dot(record.normal, UnitVector(scatter_direction));
    auto factor = mu_naught / (4 * mu * mu_naught);
    auto i = acos(Dot(UnitVector(-1 * r_in.direction()), UnitVector(record.normal) ));
    auto e = acos(Dot(UnitVector(scatter_direction), UnitVector(record.normal)));
    auto psi = findPsi(UnitVector(-1 * r_in.direction()), UnitVector(scatter_direction), UnitVector(record.normal));
    double shadow_factor = 0.0; 
    (i < e) ? shadow_factor = HapkeShadowing2(theta, i, e, psi) : shadow_factor = HapkeShadowing1(theta, i, e, psi);
    scattered = Ray(record.point, scatter_direction, r_in.time());
    auto pointAlbedo = albedo->value(record.u_coord, record.v_coord, record.point);
    auto rough_factor = (factor * (1 + (HFunction(mu_naught, pointAlbedo) * HFunction(mu, pointAlbedo)) -1));
    attenuation = albedo->value(record.u_coord, record.v_coord, record.point) * shadow_factor * rough_factor;
    return true;
}

double Hapke::HFunction(const double input, const Color albedo) const {
    auto numerator = 1 + (2 * input);
    auto denominator = 1 + (2 * input) * (sqrt(1 - (albedo.Length() / 3)));
    return numerator / denominator;
}
