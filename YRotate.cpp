#include "YRotate.h"
#include "RTWeekendUtil.h"

using namespace rtweekend_math;

YRotate::YRotate(std::shared_ptr<Hittable> p, double angle) : hittable(p)
{
    auto radians = DegreesToRadians(angle);
    sin_theta = sin(radians);
    cos_theta = cos(radians);
    hasBox = hittable->BoundingBox(0, 1, b_box);

    Point3 min(infinity, infinity, infinity);
    Point3 max(-infinity, -infinity, -infinity);

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                auto x = i * b_box.Max().x() + (1 - i) * b_box.Min().x();
                auto y = j * b_box.Max().y() + (1 - j) * b_box.Min().y();
                auto z = k * b_box.Max().z() + (1 - k) * b_box.Min().z();

                auto newx = cos_theta * x + sin_theta * z;
                auto newz = -sin_theta * x + cos_theta * z;

                Vec3 tester(newx, y, newz);

                for (int c = 0; c < 3; c++) {
                    min[c] = fmin(min[c], tester[c]);
                    max[c] = fmax(max[c], tester[c]);
                }
            }
        }
    }

    b_box = AABB(min, max);
}

bool YRotate::Hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const
{
    auto origin = r.origin();
    auto direction = r.direction();

    origin[0] = cos_theta * r.origin()[0] - sin_theta * r.origin()[2];
    origin[2] = sin_theta * r.origin()[0] + cos_theta * r.origin()[2];

    direction[0] = cos_theta * r.direction()[0] - sin_theta * r.direction()[2];
    direction[2] = sin_theta * r.direction()[0] + cos_theta * r.direction()[2];

    Ray rotated_r(origin, direction, r.time());

    if (!hittable->Hit(rotated_r, t_min, t_max, rec))
        return false;

    auto p = rec.point;
    auto normal = rec.normal;

    p[0] = cos_theta * rec.point[0] + sin_theta * rec.point[2];
    p[2] = -sin_theta * rec.point[0] + cos_theta * rec.point[2];

    normal[0] = cos_theta * rec.normal[0] + sin_theta * rec.normal[2];
    normal[2] = -sin_theta * rec.normal[0] + cos_theta * rec.normal[2];

    rec.point = p;
    rec.SetFaceNormal(rotated_r, normal);

    return true;
}

bool YRotate::BoundingBox(double time0, double time1, AABB& output_box) const
{
    output_box = b_box;
    return hasBox;
}
