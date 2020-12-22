#pragma once
#include "vec3.h"
#include "Vec3Util.h"
class Ray
{
public:
	Ray();
	Ray(const Point3& origin, const Vec3& direction);
	Point3 origin();
	Vec3 direction();
	Point3 at(double time);
	
public:
	Point3 origin_;
	Vec3 direction_;
};

