#include "Perlin.h"
#include "RTWeekendUtil.h"
#include "Vec3Util.h"

using namespace rtweekend_math;

Perlin::Perlin()
{
	randomVectors = new Vec3[point_count];
	for (int i = 0; i < point_count; ++i) {
		randomVectors[i] = UnitVector(random(-1,1));
	}

	perm_x = PerlinGeneratePerm();
	perm_y = PerlinGeneratePerm();
	perm_z = PerlinGeneratePerm();
}

Perlin::~Perlin()
{
	delete[] randomVectors;
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
	Vec3 c[2][2][2];

	for (int di = 0; di < 2; di++) 
		for (int dj = 0; dj < 2; dj++) 
			for (int dk = 0; dk < 2; dk++) 
				c[di][dj][dk] = randomVectors[
					perm_x[(i+di) & 255] ^ 
					perm_y[(j+dj) & 255] ^ 
					perm_z[(k+dk) & 255]
				];
			
	return TrilinearInterpolation(c, u, v, w);
}

double Perlin::Turbulence(const Point3& point, int depth) const
{
	auto accumulation = 0.0;
	auto temp_point = point;
	auto weight = 1.0;

	for (int i = 0; i < depth; i++) {
		accumulation += weight * Noise(temp_point);
		weight *= 0.5;
		temp_point *= 2;
	}
	return fabs(accumulation);
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

double Perlin::TrilinearInterpolation(Vec3 c[2][2][2], double u, double v, double w)
{
	auto uu = u * u * (3 - 2 * u);
	auto vv = v * v * (3 - 2 * v);
	auto ww = w * w * (3 - 2 * w);

	auto accumulation = 0.0;
	for (int i = 0; i < 2; i++) 
		for (int j = 0; j < 2; j++) 
			for (int k = 0; k < 2; k++) {
				Vec3 vectorWeight(u - i, v - j, w - k);
				accumulation += (i * uu + (1 - i) * (1 - uu)) 
					*			(j * vv + (1 - j) * (1 - vv)) 
					*			(k * ww + (1 - k) * (1 - ww)) 
					* Dot(c[i][j][k], vectorWeight);
			}
	return accumulation;
}
