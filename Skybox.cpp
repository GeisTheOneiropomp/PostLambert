#include "Skybox.h"
#include "RTUtil.h"
#include "Vec3Util.h"
using namespace rt_math;

Skybox::Skybox()
{
}

Skybox::Skybox(string input)
{
	texturePointers.push_back(make_shared<ImageTexture>(input));
}

Color Skybox::getValue(const Vec3 vector) const
{

	Vec3 unit = UnitVector(vector);
	auto theta = acos(-unit.y());
	auto phi = atan2(-unit.z(), unit.x()) + pi;
	auto u = phi / (2 * pi);
	auto v = (theta / pi);
	auto texture = texturePointers[0]->value(u, v, unit);
	return texturePointers[0]->value(u, v, unit);

}
