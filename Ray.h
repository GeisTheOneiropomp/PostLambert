#pragma once
#include "vec3.h"
namespace Vector3Namespace {
	class Ray
	{
	public:
		Ray();
		Ray(const Point3& origin, const Vec3& direction);
		Point3 origin() const;
		Vec3 direction() const;
		Point3 at(double time) const;

	public:
		Point3 origin_;
		Vec3 direction_;
	};
}

