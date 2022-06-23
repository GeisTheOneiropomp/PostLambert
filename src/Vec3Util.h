#pragma once
#include <ostream>
#include "vec3.h"

	std::ostream& operator<<(std::ostream& out, const Vec3& v);
	Vec3 operator+ (const Vec3& u, const Vec3& v);
	Vec3 operator- (const Vec3& u, const Vec3& v);
	Vec3 operator* (const Vec3& u, const Vec3& v);
	Vec3 operator/(const Vec3 u, double t);
	Vec3 operator* (const double t, const Vec3& v);
	double Dot(const Vec3& u, const Vec3& v);
	double CosAngle(const Vec3& u, const Vec3& v);
	double Angle(const Vec3& u, const Vec3& v);
	Vec3 Cross(const Vec3& u, const Vec3& v);
	Vec3 UnitVector(Vec3 u);
	Vec3 operator* (const Vec3 u, const double t);
	Vec3 random();
	Vec3 random(double min, double max);
	Vec3 RandomInUnitSphere();
	Vec3 RandomUnitVector();
	Vec3 RandomInUnitDisk();
	Vec3 RandomInHemisphere(const Vec3& normal);
	Vec3 RandomOnUnitDesk();
	Vec3 Reflect(const Vec3& v, const Vec3& normal);
	Vec3 Refract(const Vec3& uv, const Vec3 normal, double etai_over_etat);
	double findPsi(const Vec3& i, const Vec3& e, const Vec3& n);
