#pragma once
#include "Material.h"
#include "rtweekendutil.h"
#include "Vec3Util.h"
#include "SolidColor.h"
#include "Texture.h"

using std::shared_ptr;

class Lambertian :
    public Material
{
public:
    Lambertian(const Color& a);
    Lambertian(shared_ptr<Texture> a);
    virtual bool scatter(const Ray& r_in, const HitRecord& record, Color& attenuation, Ray& scattered) const override;
public:
    shared_ptr<Texture> albedo;
};

