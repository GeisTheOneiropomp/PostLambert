#include "DiffuseLight.h"
#include "SolidColor.h"
DiffuseLight::DiffuseLight(std::shared_ptr<Texture> texture) : emit(texture)
{
}

DiffuseLight::DiffuseLight(Color color) : emit(std::make_shared<SolidColor>(color))
{
}

bool DiffuseLight::scatter(const Ray& r_in, const HitRecord& record, Color& attenuation, Ray& scattered) const
{
    return false;
}

Color DiffuseLight::emitted(double u, double v, const Point3& p) const 
{
    return emit->value(u,v,p);
}
