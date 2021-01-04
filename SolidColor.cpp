#include "SolidColor.h"

SolidColor::SolidColor()
{
}

SolidColor::SolidColor(Color color) : color_value_(color)
{
}

SolidColor::SolidColor(double red, double green, double blue) : color_value_(Color(red, green, blue))
{
}

Color SolidColor::value(double u, double v, const Vec3& p) const
{
	return color_value_;
}
