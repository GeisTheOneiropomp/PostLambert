#include "Sphere.h"
#include "Vec3Util.h"
using namespace Vector3Namespace;

Sphere::Sphere()
{
}

Sphere::Sphere(Point3 center, double radius, std::shared_ptr<Material> material) 
	: center(center), radius(radius), materialPointer(material)
{
}

bool Sphere::hit(const Ray& r, double t_min, double t_max, hitRecord& rec) const
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
	rec.point = r.at(rec.t);
	Vec3 outwardNormal = (rec.point - center) / radius;
	rec.setFaceNormal(r, outwardNormal);
	rec.materialPointer = materialPointer;

	return true;
}
