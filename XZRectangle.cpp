#include "XZRectangle.h"

XZRectangle::XZRectangle()
{
}

XZRectangle::XZRectangle(double x0, double x1, double z0, double z1, double k, std::shared_ptr<Material> material)
	: x0(x0), x1(x1), z0(z0), z1(z1), k(k), material(material)
{
}

bool XZRectangle::Hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const
{
    auto t = (k - r.origin().y()) / r.direction().y();
    if (t < t_min || t > t_max) return false;
    auto x = r.origin().x() + t * r.direction().x();
    auto z = r.origin().z() + t * r.direction().z();
    if (x < x0 || x > x1 || z < z0 || z > z1) return false;
    rec.u_coord = (x - x0) / (x1 - x0);
    rec.v_coord = (z - z0) / (z1 - z0);
    rec.t = t;
    auto outward_normal = Vec3(0, 1, 0);
    rec.SetFaceNormal(r, outward_normal);
    rec.material_pointer = material;
    rec.point = r.at(t);
    return true;
}

bool XZRectangle::BoundingBox(double time0, double time1, AABB& output_box) const
{
	output_box = AABB(Point3(x0, z0, k - 0.0001), Point3(x1, z1, k + 0.0001));
	return false;
}
