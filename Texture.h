#pragma once
#include "Vec3.h"
class Texture
{
public:
	virtual Color value(double u, double v, const Point3& p) const = 0;
};

