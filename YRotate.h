#pragma once
#include "Hittable.h"
class YRotate :
    public Hittable
{
public:
    YRotate(std::shared_ptr<Hittable> p, double angle);

    virtual bool Hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const override;

    virtual bool BoundingBox(double time0, double time1, AABB& output_box) const override;

public:
    std::shared_ptr<Hittable> hittable;
    double sin_theta;
    double cos_theta;
    bool hasBox;
    AABB b_box;
};

