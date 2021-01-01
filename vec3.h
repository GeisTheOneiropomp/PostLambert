#pragma once
#include <cmath>

	class Vec3
	{
	public:

		Vec3();
		Vec3(double e0, double e1, double e2);
		double x();
		double y();
		double z();
		Vec3 operator-() const;
		double operator[] (int i);
		Vec3& operator+= (const Vec3 v);
		Vec3& operator*= (const double t);
		Vec3& operator/= (const double t);
		double Length();
		double LengthSquared();
		bool nearZero() const;

	public:
		double e[3];
	};

	// Type aliases for vec3
	using Point3 = Vec3;   // 3D point
	using Color = Vec3;    // RGB color