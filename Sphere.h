#pragma once
#include "vec3.h"
#include "Hittable.h"
#include "Vec3Util.h"
#include "RTUtil.h"

class Sphere : public Hittable 
{
public:
	Sphere();
	Sphere(Point3 center, double radius, std::shared_ptr<Material> material);
	virtual bool Hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const override;
	virtual bool BoundingBox(double time0, double time1, AABB& output_box) const override;
public:
	Point3 center;
	double radius;
	std::shared_ptr<Material> materialPointer;

private:
	static void getSphereUV(const Point3& point, double& u, double& v);
};

