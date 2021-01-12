#include "YZRectangle.h"

YZRectangle::YZRectangle()
{
}

YZRectangle::YZRectangle(double y0, double y1, double z0, double z1, double k, std::shared_ptr<Material> material)
	: y0(y0), y1(y1), z0(z0), z1(z1), k(k), material(material)
{
}

bool YZRectangle::Hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const
{
    auto t = (k - r.origin().x()) / r.direction().x();
    if (t < t_min || t > t_max) return false;
    auto y = r.origin().y() + t * r.direction().y();
    auto z = r.origin().z() + t * r.direction().z();
    if (y < y0 || y > y1 || z < z0 || z > z1) return false;
    rec.u_coord = (y - y0) / (y1 - y0);
    rec.v_coord = (z - z0) / (z1 - z0);
    rec.t = t;
    auto outward_normal = Vec3(1, 0, 0);
    rec.SetFaceNormal(r, outward_normal);
    rec.material_pointer = material;
    rec.point = r.at(t);
    return true;
}

bool YZRectangle::BoundingBox(double time0, double time1, AABB& output_box) const
{
	output_box = AABB(Point3(k - 0.0001, y0, z0), Point3(k + 0.0001, y1, z1));
	return false;
}
