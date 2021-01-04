#pragma once
#include "Vec3.h"
#include "Ray.h"
using namespace Vector3Namespace;


struct HitRecord;

class Material {
public:
	virtual bool scatter(const Ray& r_in, const HitRecord& record, Color& attenuation, Ray& scattered)
		const = 0;
};