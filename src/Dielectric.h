#pragma once
#include "Material.h"
#include "rtutil.h"
class Dielectric :
    public Material
{
public:
    Dielectric(double refractiveIndex);
    virtual bool scatter(const Ray& r_in, const HitRecord& record, Color& attenuation, Ray& scattered) const override;
public:
    double refractiveIndex;
private:
    static double SchlickReflectance(double cosine, double ri);
};

