#pragma once
#include <ostream>
#include "vec3.h"
namespace Vector3Namespace
{
	std::ostream& operator<<(std::ostream& out, const Vec3& v);
	Vec3 operator+ (const Vec3& u, const Vec3& v);
	Vec3 operator- (const Vec3& u, const Vec3& v);
	Vec3 operator* (const Vec3& u, const Vec3& v);
	Vec3 operator/(const Vec3 u, double t);
	Vec3 operator* (double t, const Vec3& v);
	double dot(const Vec3& u, const Vec3& v);
	Vec3 cross(const Vec3& u, const Vec3& v);
	Vec3 unit_vector(Vec3 u);
	Vec3 operator* (const Vec3 u, double t);
	static Vec3 random();
	static Vec3 random(double min, double max);
	Vec3 randomInUnitSphere();
	Vec3 randomUnitVector();
	Vec3 randomInHemisphere(const Vec3& normal);

};

