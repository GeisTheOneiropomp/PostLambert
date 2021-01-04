#include "AABB.h"
#include <xstring>

AABB::AABB()
{
}

AABB::AABB(const Point3& a, const Point3& b) : minimum(a), maximum(b)
{
}

Point3 AABB::Min() const
{
	return minimum;
}

Point3 AABB::Max() const
{
	return maximum;
}

bool AABB::hit(const Ray& r, double t_min, double t_max) const
{
    for (int a = 0; a < 3; a++) {
        auto invD = 1.0f / r.direction()[a];
        auto t0 = (Min()[a] - r.origin()[a]) * invD;
        auto t1 = (Max()[a] - r.origin()[a]) * invD;
        if (invD < 0.0f)
            std::swap(t0, t1);
        t_min = t0 > t_min ? t0 : t_min;
        t_max = t1 < t_max ? t1 : t_max;
        if (t_max <= t_min)
            return false;
    }
    return true;
}

AABB surrounding_box(AABB box0, AABB box1)
{
    Point3 small(fmin(box0.Min().x(), box1.Min().x()),
        fmin(box0.Min().y(), box1.Min().y()),
        fmin(box0.Min().z(), box1.Min().z()));

    Point3 big(fmax(box0.Max().x(), box1.Max().x()),
        fmax(box0.Max().y(), box1.Max().y()),
        fmax(box0.Max().z(), box1.Max().z()));

    return AABB(small, big);
}
