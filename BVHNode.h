#pragma once
#include "Hittable.h"
#include "HittableList.h"
#include "RTUtil.h"
class BVHNode :
    public Hittable
{
public:
    BVHNode();
    BVHNode(const HittableList& list, double time0, double time1);
    BVHNode(const std::vector<shared_ptr<Hittable>>& source_objects, size_t start, size_t end, double time0, double time1);
    virtual bool Hit(const Ray& r, double t_min, double t_max, HitRecord& record) const override;
    virtual bool BoundingBox(double time0, double time1, AABB& output_box) const override;

public:
    shared_ptr<Hittable> left;
    shared_ptr<Hittable> right;
    AABB box;
};

bool box_x_compare(const shared_ptr<Hittable> a, const shared_ptr<Hittable> b);
bool box_y_compare(const shared_ptr<Hittable> a, const shared_ptr<Hittable> b);
bool box_z_compare(const shared_ptr<Hittable> a, const shared_ptr<Hittable> b);
bool box_compare(const shared_ptr<Hittable> a, const shared_ptr<Hittable> b, int axis);

