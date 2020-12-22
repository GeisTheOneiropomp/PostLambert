#pragma once
#include <ostream>
#include "vec3.h"
namespace Vec3Util
{
	inline std::ostream& operator<<(std::ostream& out, const Vec3& v);
	inline Vec3 operator+ (const Vec3& u, const Vec3& v);
	inline Vec3 operator- (const Vec3& u, const Vec3& v);
	inline Vec3 operator* (const Vec3& u, const Vec3& v);
	inline Vec3 operator/(const Vec3 u, double t);
	inline Vec3 operator* (double t, const Vec3& v);
	inline double dot(const Vec3& u, const Vec3& v);
	inline Vec3 cross(const Vec3& u, const Vec3& v);
	inline Vec3 unit_vector(Vec3 u);
	inline Vec3 operator* (const Vec3 u, double t);

};

