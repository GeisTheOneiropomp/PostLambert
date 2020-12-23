#include "Sphere.h"
#include "Vec3Util.h"
using namespace Vector3Namespace;

Sphere::Sphere()
{
}

Sphere::Sphere(Point3 center, double radius) : center(center), radius(radius)
{
}

bool Sphere::hit(const Ray& r, double t_min, double t_max, hit_record& rec) const
{
	Vec3 origin = r.origin() - center;
	auto a = r.direction().LengthSquared();
	auto half_b = dot(origin, r.direction());
	auto c = origin.LengthSquared() - radius * radius;

	auto discriminant = half_b * half_b - a * c;
	if (discriminant < 0) return false;
	auto sqrtd = sqrt(discriminant);

	auto root = (-half_b - sqrtd) / a;
	if (root < t_min || t_max < root) {
		root = (-half_b + sqrtd) / a;
		if (root < t_min || t_max < root) {
			return false;
		}
	}

	rec.t = root;
	rec.p = r.at(rec.t);
	Vec3 outwardNormal = (rec.p - center) / radius;
	rec.setFaceNormal(r, outwardNormal);

	return true;
}
