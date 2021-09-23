#pragma once
#include "Material.h"
class Diffraction : public Material
{
public:
    Diffraction();
    virtual bool scatter(const Ray& r_in, const HitRecord& record, Color& attenuation, Ray& scattered) const override;
};

