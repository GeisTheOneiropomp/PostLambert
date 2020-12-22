#include "Ray.h"

using namespace Vec3Util;
Ray::Ray() {

}

Ray::Ray(const Point3& origin, const Vec3& direction) : origin_(origin), direction_(direction)
{
}

Point3 Ray::origin()
{
	return origin_;
}

Vec3 Ray::direction()
{
	return direction_;
}

Point3 Ray::at(double time)
{
	return origin_ + (time * direction_);
}

