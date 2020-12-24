#pragma once
#include "vec3.h"
#include "Hittable.h"
using namespace Vector3Namespace;
class Sphere : public Hittable 
{
public:
	Sphere();
	Sphere(Point3 center, double radius, std::shared_ptr<Material> material);
	virtual bool hit(const Ray& r, double t_min, double t_max, hitRecord& rec) const override;
public:
	Point3 center;
	double radius;
	std::shared_ptr<Material> materialPointer;
};

