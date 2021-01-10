#include "Box.h"
#include "XYRectangle.h"
#include "XZRectangle.h"
#include "YZRectangle.h"

Box::Box()
{
}

Box::Box(const Point3& p0, const Point3& p1, std::shared_ptr<Material> material)
{
    box_min = p0;
    box_max = p1;

    sides.add(make_shared<XYRectangle>(p0.x(), p1.x(), p0.y(), p1.y(), p1.z(), material));
    sides.add(make_shared<XYRectangle>(p0.x(), p1.x(), p0.y(), p1.y(), p0.z(), material));

    sides.add(make_shared<XZRectangle>(p0.x(), p1.x(), p0.z(), p1.z(), p1.y(), material));
    sides.add(make_shared<XZRectangle>(p0.x(), p1.x(), p0.z(), p1.z(), p0.y(), material));

    sides.add(make_shared<YZRectangle>(p0.y(), p1.y(), p0.z(), p1.z(), p1.x(), material));
    sides.add(make_shared<YZRectangle>(p0.y(), p1.y(), p0.z(), p1.z(), p0.x(), material));
}

bool Box::Hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const
{
    return sides.Hit(r, t_min, t_max, rec);
}

bool Box::BoundingBox(double time0, double time1, AABB& output_box) const
{
    output_box = AABB(box_min, box_max);
    return true;
}
