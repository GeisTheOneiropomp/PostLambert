#pragma once
#include "Hittable.h"
class XZRectangle :
    public Hittable
{
public:
    XZRectangle();
    XZRectangle(double x0, double x1, double z0, double z1, double k, std::shared_ptr<Material> material);
    virtual bool Hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const override;
    virtual bool BoundingBox(double time0, double time1, AABB& output_box) const override;

public:
    std::shared_ptr<Material> material;
    double x0, x1, z0, z1, k;
};

