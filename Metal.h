#pragma once
#include "Material.h"
#include "Vec3Util.h"
class Metal :
    public Material
{
public:
    Metal(const Color& albedo, double fuzziness);
    virtual bool scatter(const Ray& r_in, const hitRecord& record, Color& attenuation, Ray& scattered) const override;

public:
    Color albedo;
    double fuzziness;
};

