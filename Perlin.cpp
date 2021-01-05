#include "Perlin.h"
#include "RTWeekendUtil.h"

using namespace rtweekend_math;

Perlin::Perlin()
{
	random_floats = new double[point_count];
	for (int i = 0; i < point_count; ++i) {
		random_floats[i] = RandomDouble();
	}

	perm_x = PerlinGeneratePerm();
	perm_y = PerlinGeneratePerm();
	perm_z = PerlinGeneratePerm();
}

Perlin::~Perlin()
{
	delete[] random_floats;
	delete[] perm_x;
	delete[] perm_y;
	delete[] perm_z;
}

double Perlin::Noise(const Point3& point) const
{
	auto i = static_cast<int>(4 * point.x()) & 255;
	auto j = static_cast<int>(4 * point.y()) & 255;
	auto k = static_cast<int>(4 * point.z()) & 255;
	return random_floats[perm_x[i] ^ perm_y[j] ^ perm_z[k]];
}

int* Perlin::PerlinGeneratePerm()
{
	auto p = new int[point_count];
	for (int i = 0; i < Perlin::point_count; i++) {
		p[i] = i;
	}

	Permute(p, point_count);
	return p;
}

void Perlin::Permute(int* p, int n)
{
	for (int i = n - 1; i > 0; i--) {
		int target = RandomInt(0, i);
		int temp = p[i];
		p[i] = p[target];
		p[target] = temp;
	}
}
