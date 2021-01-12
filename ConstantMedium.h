#pragma once
#include "Hittable.h"
#include "Translate.h"
#include <memory>
#include "Texture.h"
#include "Isotropic.h"
using std::shared_ptr;

class ConstantMedium :
    public Hittable
{
public:
    ConstantMedium(shared_ptr<Hittable> b, double d, shared_ptr<Texture> a);
    ConstantMedium(shared_ptr<Hittable> b, double d, Color c);

    virtual bool Hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const override;

    virtual bool BoundingBox(double time0, double time1, AABB& output_box) const override;

public:
    shared_ptr<Hittable> boundary;
    shared_ptr<Material> phase_function;
    double negative_inverse_density;
};

