#pragma once
#include "Hittable.h"
#include "HittableList.h"
class Box :
    public Hittable
{
public:
    Box();
    Box(const Point3& p0, const Point3& p1, std::shared_ptr<Material> material);

    virtual bool Hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const override;

    virtual bool BoundingBox(double time0, double time1, AABB& output_box) const override;

public:
    Point3 box_min;
    Point3 box_max;
    HittableList sides;

};

