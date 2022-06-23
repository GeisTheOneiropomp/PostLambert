#include "Isotropic.h"
#include "SolidColor.h"
#include "Vec3Util.h"
#include "Hittable.h"
Isotropic::Isotropic(Color c) : albedo(std::make_shared<SolidColor>(c))
{
}

Isotropic::Isotropic(shared_ptr<Texture> a) : albedo(a)
{
}

bool Isotropic::scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered) const
{
    scattered = Ray(rec.point, RandomInUnitSphere(), r_in.time());
    attenuation = albedo->value(rec.u_coord, rec.v_coord, rec.point);
    return true;
}
