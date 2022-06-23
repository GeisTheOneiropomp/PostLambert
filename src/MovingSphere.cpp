#include "MovingSphere.h"
#include "Vec3Util.h"
using namespace Vector3Namespace;

MovingSphere::MovingSphere()
{
}

MovingSphere::MovingSphere(Point3 center0, Point3 center1, double _time0, 
	double _time1, double radius, std::shared_ptr<Material> material) :
	center0(center0), center1(center1), time0(_time0), time1(_time1), radius(radius),
	materialPointer(material)
{
}

bool MovingSphere::Hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const
{
	Vec3 origin = r.origin() - center(r.time());
	auto a = r.direction().LengthSquared();
	auto half_b = Dot(origin, r.direction());
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
	Vec3 outwardNormal = (rec.point - center(r.time())) / radius;
	rec.SetFaceNormal(r, outwardNormal);
	rec.material_pointer = materialPointer;
	return true;
}

Point3 MovingSphere::center(double time) const {
	return center0 + ((time - time0) / (time1 - time0)) * (center1 - center0);
}

