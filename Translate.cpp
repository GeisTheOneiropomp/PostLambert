#include "Translate.h"

Translate::Translate(std::shared_ptr<Hittable> p, const Vec3& displacement)
    : hittable(p), offset(displacement)
{
}

bool Translate::Hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const
{
    Ray moved_ray(r.origin() - offset, r.direction(), r.time());
    if (!hittable->Hit(moved_ray, t_min, t_max, rec)) return false;
    rec.point += offset;
    rec.SetFaceNormal(moved_ray, rec.normal);
    return true;
}

bool Translate::BoundingBox(double time0, double time1, AABB& output_box) const
{
    if (!hittable->BoundingBox(time0, time1, output_box)) return false;
    output_box = AABB(output_box.Min() + offset, output_box.Max() + offset);
    return true;
}
