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

	auto u = point.x() - floor(point.x());
	auto v = point.y() - floor(point.y());
	auto w = point.z() - floor(point.z());

	auto i = static_cast<int>(floor(point.x()));
	auto j = static_cast<int>(floor(point.y()));
	auto k = static_cast<int>(floor(point.z()));
	double c[2][2][2];

	for (int di = 0; di < 2; di++) 
		for (int dj = 0; dj < 2; dj++) 
			for (int dk = 0; dk < 2; dk++) 
				c[di][dj][dk] = random_floats[
					perm_x[(i+di) & 255] ^ 
					perm_y[(j+dj) & 255] ^ 
					perm_z[(k+dk) & 255]
				];
			
	return TrilinearInterpolation(c, u, v, w);
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

double Perlin::TrilinearInterpolation(double c[2][2][2], double u, double v, double w)
{
	auto accumulation = 0.0;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			for (int k = 0; k < 2; k++) {
				accumulation += (i * u + (1 - i) * (1 - u)) *
					(j * v + (1 - j) * (1 - v)) *
					(k * w + (1 - k) * (1 - w)) * c[i][j][k];
			}
		}
	}
	return accumulation;
}
