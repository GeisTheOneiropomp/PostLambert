#pragma once
#include "vec3.h"
#include "Ray.h"

using namespace Vector3Namespace;

struct hit_record {
	Point3 p;
	Vec3 normal;
	double t;
	bool front_face;

	inline void setFaceNormal(const Ray& r, const Vec3& outwardNormal) {
		front_face = dot(r.direction(), outwardNormal) < 0;
		normal = front_face ? outwardNormal : -outwardNormal;
	}
};

class Hittable
{
public:
	virtual bool hit(const Ray& r, double t_min, double t_max, hit_record& rec) const = 0;
};

