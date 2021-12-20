#include "Dielectric.h"
#include "Hittable.h"

using namespace rt_math;

Dielectric::Dielectric(double refractiveIndex) : refractiveIndex(refractiveIndex)
{
}

bool Dielectric::scatter(const Ray& r_in, const HitRecord& record, Color& attenuation, Ray& scattered) const
{
	attenuation = Color(1.0, 1.0, 1.0);
	double refraction_ratio = record.front_face ? (1.0 / refractiveIndex) : refractiveIndex;
	Vec3 unit_direction = UnitVector(r_in.direction());
	double cosineTheta = fmin(Dot(-unit_direction, record.normal), 1.0);
	double sineTheta = sqrt(1.0 - cosineTheta * cosineTheta);
	bool cannotRefract = refraction_ratio * sineTheta > 1.0;
	Vec3 direction;
	if (cannotRefract || SchlickReflectance(cosineTheta, refraction_ratio) > RandomDouble()) {
		direction = Reflect(unit_direction, record.normal);
	}
	else {
		direction = Refract(unit_direction, record.normal, refraction_ratio);
	}
	scattered = Ray(record.point, direction, r_in.time());
	return true;
}

double Dielectric::SchlickReflectance(double cosine, double ri)
{
	auto r0 = (1 - ri) / (1 + ri);
	r0 = r0 * r0;
	return r0 + (1 - r0) * pow((1 - cosine), 5);
}
