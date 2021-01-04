#pragma once
#include "vec3.h"
#include "Ray.h"
#include "Vec3Util.h"
#include "Material.h"
#include "AABB.h"

using namespace Vector3Namespace;

struct HitRecord {
	Point3 point;
	Vec3 normal;
	std::shared_ptr<Material> material_pointer;
	double t;
	bool front_face;

	inline void SetFaceNormal(const Ray& r, const Vec3& outward_normal) {
		front_face = Dot(r.direction(), outward_normal) < 0;
		normal = front_face ? outward_normal : -outward_normal;
	}
};

class Hittable
{
public:
	virtual bool Hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const = 0;
	virtual bool BoundingBox(double time0, double time1, AABB& output_box) const = 0;
};

