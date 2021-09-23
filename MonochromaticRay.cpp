#include "MonochromaticRay.h"

Vector3Namespace::MonochromaticRay::MonochromaticRay()
{
	wavelength = 0.0;
	intensity = 0.0;
	ray = Ray();
}

Vector3Namespace::MonochromaticRay::MonochromaticRay(const Point3& origin, const Vec3& direction, double time, 
	double wavelength, double intensity) :
	wavelength(wavelength), intensity(intensity), ray(Ray(origin, direction, time))
{
}
