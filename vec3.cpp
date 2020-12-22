#include "vec3.h"

namespace Vector3Namespace {

	Vec3::Vec3() : e{ 0,0,0 }
	{

	}

	Vec3::Vec3(double e0, double e1, double e2) : e{ e0, e1, e2 }
	{
	}

	double Vec3::x()
	{
		return e[0];
	}

	double Vec3::y()
	{
		return e[1];
	}

	double Vec3::z()
	{
		return e[2];
	}

	Vec3 Vec3::operator-()
	{
		return Vec3(-e[0], -e[1], -e[2]);
	}

	double Vec3::operator[](int i)
	{
		return e[i];
	}

	Vec3& Vec3::operator+=(const Vec3 v)
	{
		e[0] += v.e[0];
		e[1] += v.e[1];
		e[2] += v.e[2];
		return *this;
	}

	Vec3& Vec3::operator*=(const double t)
	{
		e[0] *= t;
		e[1] *= t;
		e[2] *= t;
		return *this;
	}

	Vec3& Vec3::operator/=(const double t)
	{
		return *this *= 1 / t;
	}

	double Vec3::Length()
	{
		return std::sqrt(LengthSquared());
	}

	double Vec3::LengthSquared()
	{
		return (e[0] * e[0]) + (e[1] * e[1]) + (e[2] * e[2]);
	}

}
