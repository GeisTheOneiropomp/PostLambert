#pragma once
#include "vec3.h"
#include "Hittable.h"
using namespace Vector3Namespace;
class Sphere : public Hittable 
{
public:
	Sphere();
	Sphere(Point3 center, double radius);
	virtual bool hit(const Ray& r, double t_min, double t_max, hit_record& rec) const override;
public:
	Point3 center;
	double radius;
};

