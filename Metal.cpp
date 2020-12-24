#include "Metal.h"
#include "Hittable.h"
Metal::Metal(const Color& albedo, double fuzziness) 
	: albedo(albedo), fuzziness(fuzziness > 1 ? 1 : fuzziness)
{
}

bool Metal::scatter(const Ray& r_in, const hitRecord& record, Color& attenuation, Ray& scattered) const
{
	Vec3 reflected = reflect(unit_vector(r_in.direction()), record.normal);
	scattered = Ray(record.point, reflected + fuzziness*randomInUnitSphere());
	attenuation = albedo;
	return (dot(scattered.direction(), record.normal) > 0);
}
