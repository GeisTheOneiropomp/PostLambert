#pragma once
#include "Texture.h"
#include "Perlin.h"
#include "Vec3Util.h"
class NoiseTexture : public Texture
{
public:
	NoiseTexture();
	virtual Color value(double u, double v, const Point3& p) const override;
	Perlin noise;
};

