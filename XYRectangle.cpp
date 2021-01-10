#include "XYRectangle.h"

XYRectangle::XYRectangle()
{
}

XYRectangle::XYRectangle(double x0, double x1, double y0, double y1, double k, std::shared_ptr<Material> material)
    : x0(x0), x1(x1), y0(y0), y1(y1), k(k), material(material)
{
}

bool XYRectangle::Hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const
{
    auto t = (k - r.origin().z()) / r.direction().z();
    if (t < t_min || t > t_max) return false;
    auto x = r.origin().x() + t * r.direction().x();
    auto y = r.origin().y() + t * r.direction().y();
    if (x < x0 || x > x1 || y < y0 || y > y1) return false;
    rec.u_coord = (x - x0) / (x1 - x0);
    rec.v_coord = (y - y0) / (y1 - y0);
    rec.t = t;
    auto outward_normal = Vec3(0, 0, 1);
    rec.SetFaceNormal(r, outward_normal);
    rec.material_pointer = material;
    rec.point = r.at(t);
    return true;
}

bool XYRectangle::BoundingBox(double time0, double time1, AABB& output_box) const
{
    output_box = AABB(Point3(x0, y0, k - 0.0001), Point3(x1, y1, k + 0.0001));
    return false;
}
