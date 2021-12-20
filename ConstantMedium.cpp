#include "ConstantMedium.h"
#include "rtutil.h"

using namespace rt_math;

ConstantMedium::ConstantMedium(shared_ptr<Hittable> b, double d, shared_ptr<Texture> texture) 
	: boundary(b), negative_inverse_density(-1 / d), phase_function(std::make_shared<Isotropic>(texture))
{}

ConstantMedium::ConstantMedium(shared_ptr<Hittable> b, double d, Color c) 
	: boundary(b), negative_inverse_density(-1 / d), phase_function(std::make_shared<Isotropic>(c))
{
}

bool ConstantMedium::Hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const
{
    // Print occasional samples when debugging. To enable, set enableDebug true.
    HitRecord rec1, rec2;

    if (!boundary->Hit(r, -infinity, infinity, rec1))
        return false;

    if (!boundary->Hit(r, rec1.t + 0.0001, infinity, rec2))
        return false;

    if (rec1.t < t_min) rec1.t = t_min;
    if (rec2.t > t_max) rec2.t = t_max;

    if (rec1.t >= rec2.t)
        return false;

    if (rec1.t < 0)
        rec1.t = 0;

    const auto ray_length = r.direction().Length();
    const auto distance_inside_boundary = (rec2.t - rec1.t) * ray_length;
    const auto hit_distance = negative_inverse_density * log(RandomDouble());

    if (hit_distance > distance_inside_boundary)
        return false;

    rec.t = rec1.t + hit_distance / ray_length;
    rec.point = r.at(rec.t);


    rec.normal = Vec3(1, 0, 0);  // arbitrary
    rec.front_face = true;     // also arbitrary
    rec.material_pointer = phase_function;

    return true;
}

bool ConstantMedium::BoundingBox(double time0, double time1, AABB& output_box) const
{
	return boundary->BoundingBox(time0, time1, output_box);
}
