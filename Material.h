#pragma once
#include "Vec3.h"
#include "Ray.h"
using namespace Vector3Namespace;


struct hitRecord;

class Material {
public:
	virtual bool scatter(const Ray& r_in, const hitRecord& record, Color& attenuation, Ray& scattered)
		const = 0;
};