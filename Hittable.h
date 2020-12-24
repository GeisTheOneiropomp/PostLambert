#pragma once
#include "vec3.h"
#include "Ray.h"
#include "Vec3Util.h"
#include "Material.h"

using namespace Vector3Namespace;

struct hitRecord {
	Point3 point;
	Vec3 normal;
	std::shared_ptr<Material> materialPointer;
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
	virtual bool hit(const Ray& r, double t_min, double t_max, hitRecord& rec) const = 0;
};

