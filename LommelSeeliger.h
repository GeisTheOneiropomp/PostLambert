#pragma once
#include "Material.h"
class LommelSeeliger :
    public Material
{
public:
    LommelSeeliger(const Color& a);
    virtual bool scatter(const Ray& r_in, const HitRecord& record, Color& attenuation, Ray& scattered) const override;
public:
    Color albedo;
};

