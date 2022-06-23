#pragma once
#include "vec3.h"
namespace Vector3Namespace {
	class Ray
	{
	public:
		Ray();
		Ray(const Point3& origin, const Vec3& direction, double time = 0.0);
		Point3 origin() const;
		Vec3 direction() const;
		double time() const;
		Point3 at(double time) const;

	public:
		Point3 origin_;
		Vec3 direction_;
		double time_;
	};
}

