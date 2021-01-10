#pragma once
#include "Hittable.h"
class YZRectangle :
    public Hittable
{
public:
    YZRectangle();
    YZRectangle(double y0, double y1, double z0, double z1, double k, std::shared_ptr<Material> material);
    virtual bool Hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const override;
    virtual bool BoundingBox(double time0, double time1, AABB& output_box) const override;

public:
    std::shared_ptr<Material> material;
    double y0, y1, z0, z1, k;
};

