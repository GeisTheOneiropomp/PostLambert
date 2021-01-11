#pragma once
#include "Hittable.h"
class Translate :
    public Hittable
{
public:
    Translate(std::shared_ptr<Hittable> p, const Vec3& displacement);
    virtual bool Hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const override;

    virtual bool BoundingBox(double time0, double time1, AABB& output_box) const override;
public:
    std::shared_ptr<Hittable> hittable;
    Vec3 offset;
};

