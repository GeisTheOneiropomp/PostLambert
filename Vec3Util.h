#pragma once
#include <ostream>
#include "vec3.h"

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
	Vec3 random();
	Vec3 random(double min, double max);
	Vec3 RandomInUnitSphere();
	Vec3 RandomUnitVector();
	Vec3 RandomInUnitDisk();
	Vec3 RandomInHemisphere(const Vec3& normal);
	Vec3 reflect(const Vec3& v, const Vec3& normal);
	Vec3 refract(const Vec3& uv, const Vec3 normal, double etai_over_etat);

