#include "Ray.h"
#include "Vec3Util.h"
namespace Vector3Namespace {
	Ray::Ray()
	{
	}

	Ray::Ray(const Point3& origin, const Vec3& direction) : origin_(origin), direction_(direction)
	{
	}

	Point3 Ray::origin() const
	{
		return origin_;
	}

	Vec3 Ray::direction() const
	{
		return direction_;
	}

	Point3 Ray::at(double time) const
	{
		return origin_ + (time * direction_);
	}
}
