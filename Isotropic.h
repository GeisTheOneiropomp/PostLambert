#pragma once
#include "Material.h"
#include "Texture.h"
#include <memory>
using std::shared_ptr;

class Isotropic :
    public Material
{
public:
    Isotropic(Color c);
    Isotropic(shared_ptr<Texture> a);

    virtual bool scatter( const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered) const override;

public:
    shared_ptr<Texture> albedo;
};

