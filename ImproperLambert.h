#pragma once
#include "Material.h"
class ImproperLambert :
    public Material
{
public:
    ImproperLambert(const Color& a);
    virtual bool scatter(const Ray& r_in, const hitRecord& record, Color& attenuation, Ray& scattered) const override;
public:
    Color albedo;
};