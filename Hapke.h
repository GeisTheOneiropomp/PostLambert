#pragma once
#include "Material.h"
#include "Texture.h"
#include <memory>

using std::shared_ptr;
class Hapke :
    public Material
{
public:
    Hapke(const Color& a, const double theta);
    Hapke(shared_ptr<Texture> a, const double theta);
    virtual bool scatter(const Ray& r_in, const HitRecord& record, Color& attenuation, Ray& scattered) const override;

private:
    double HFunction(const double input, const Color albedo) const;
    double ScatterMode1(const Ray& r_in, const HitRecord& record, Color& attenuation, Ray& scattered) const;
    
public:
    shared_ptr<Texture> albedo;
    double theta;
};

