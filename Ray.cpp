#include "Ray.h"
#include "Vec3Util.h"
namespace Vector3Namespace {
	Ray::Ray()
	{
	}

	Ray::Ray(const Point3& origin, const Vec3& direction, double time) 
		: origin_(origin), direction_(direction), time_(time)
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

	double Ray::time() const 
	{
		return time_;
	}

	Point3 Ray::at(double time) const
	{
		return origin_ + (time * direction_);
	}
}
