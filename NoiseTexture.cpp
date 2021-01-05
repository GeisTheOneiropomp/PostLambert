#include "NoiseTexture.h"

NoiseTexture::NoiseTexture()
{
}

Color NoiseTexture::value(double u, double v, const Point3& p) const
{
	return Color(1, 1, 1) * noise.Noise(p);
}
