#include "Metal.h"
#include "Hittable.h"
Metal::Metal(const Color& albedo, double fuzziness) 
	: albedo(albedo), fuzziness(fuzziness > 1 ? 1 : fuzziness)
{
}

bool Metal::scatter(const Ray& r_in, const HitRecord& record, Color& attenuation, Ray& scattered) const
{
	Vec3 reflected = Reflect(UnitVector(r_in.direction()), record.normal);
	scattered = Ray(record.point, reflected + fuzziness*RandomInUnitSphere(), r_in.time());
	attenuation = albedo;
	return (Dot(scattered.direction(), record.normal) > 0);
}
