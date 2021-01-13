#pragma once
#include "Material.h"
#include "Texture.h"
#include <memory>

using std::shared_ptr;

class Minnaert :
    public Material
{
public:
    Minnaert(const Color& a, const double exponent);
    Minnaert(shared_ptr<Texture> a, const double exponent);
    virtual bool scatter(const Ray& r_in, const HitRecord& record, Color& attenuation, Ray& scattered) const override;
public:
    shared_ptr<Texture> albedo;
    double exponent;
};

