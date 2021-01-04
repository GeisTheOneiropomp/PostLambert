#pragma once

#include "hittable.h"
#include <memory>
#include <vector>

using std::shared_ptr;
using std::make_shared;

class HittableList : public Hittable
{
public: 
	HittableList();
	HittableList(shared_ptr<Hittable> object);
	void clear();
	void add(shared_ptr<Hittable> object);
	virtual bool Hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const override;
	virtual bool BoundingBox(double time0, double time1, AABB& output_box) const override;
public:
	std::vector<shared_ptr<Hittable>> objects;

};

