#pragma once
#include "Material.h"
#include "Texture.h"
#include <memory>

 
class DiffuseLight :
    public Material
{
public:
    DiffuseLight(std::shared_ptr<Texture> texture);
    DiffuseLight(Color color);

    virtual bool scatter(const Ray& r_in, const HitRecord& record, Color& attenuation, Ray& scattered);
    virtual Color emitted(double u, double v, const Point3& p) const override;

public:
    std::shared_ptr<Texture> emit;
};

