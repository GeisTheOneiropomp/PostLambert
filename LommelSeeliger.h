#pragma once
#include "Material.h"
#include "Texture.h"
#include <memory>

using std::shared_ptr;

class LommelSeeliger :
    public Material
{
public:
    LommelSeeliger(const Color& a);
    LommelSeeliger(shared_ptr<Texture> a);
    virtual bool scatter(const Ray& r_in, const HitRecord& record, Color& attenuation, Ray& scattered) const override;
public:
    shared_ptr<Texture> albedo;
};

