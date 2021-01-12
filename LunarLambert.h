#pragma once
#include "Material.h"
#include <memory>
#include "Texture.h"

using std::shared_ptr;

class LunarLambert :
    public Material
{
public:
        LunarLambert(const Color & a, const double a_coefficient, const double b_coefficient);
        LunarLambert(shared_ptr<Texture> a, const double a_coefficient, const double b_coefficient);
        virtual bool scatter(const Ray& r_in, const HitRecord& record, Color& attenuation, Ray& scattered) const override;
public:
        shared_ptr<Texture> albedo;
        double a_coefficient;
        double b_coefficient;
};

