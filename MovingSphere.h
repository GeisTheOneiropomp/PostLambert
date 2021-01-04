#pragma once

#include "Hittable.h"
#include "RTWeekendUtil.h"
class MovingSphere : public Hittable
{
public:
    MovingSphere();
    MovingSphere(Point3 center0, Point3 center1, double _time0, double _time1, double radius, std::shared_ptr<Material> material);
    virtual bool Hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const override;
    Point3 center(double time) const;
    virtual bool BoundingBox(double _time0, double _time1, AABB& output_box) const override;

public:
    Point3 center0, center1;
    double time0, time1;
    double radius;
    std::shared_ptr<Material> materialPointer;
};

