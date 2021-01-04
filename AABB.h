#pragma once
#include "Vec3.h"
#include "Ray.h"
using namespace Vector3Namespace;
class AABB
{
public:
	AABB();
	AABB(const Point3& a, const Point3& b);
	Point3 Min() const;
	Point3 Max() const;
	
	bool hit(const Ray& r, double t_min, double t_max) const;
	Point3 minimum;
	Point3 maximum;
};

AABB surrounding_box(AABB box0, AABB box1);
