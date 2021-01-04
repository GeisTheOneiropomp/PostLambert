#pragma once
#include "Material.h"
#include "rtweekendutil.h"
#include "Vec3Util.h"

class Lambertian :
    public Material
{
public:
    Lambertian(const Color& a);
    virtual bool scatter(const Ray& r_in, const HitRecord& record, Color& attenuation, Ray& scattered) const override;
public:
    Color albedo;
};

