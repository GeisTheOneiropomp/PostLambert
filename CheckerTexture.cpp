#include "CheckerTexture.h"
using std::make_shared;

CheckerTexture::CheckerTexture()
{
}

CheckerTexture::CheckerTexture(shared_ptr<Texture> even, shared_ptr<Texture> odd)
	: even(even), odd(odd)
{
}

CheckerTexture::CheckerTexture(Color c1, Color c2)
	: odd(make_shared<SolidColor>(c1)) , even(make_shared<SolidColor>(c2))
{
}

Color CheckerTexture::value(double u, double v, const Point3& p) const
{
    auto sines = sin(10 * p.x()) * sin(10 * p.y()) * sin(10 * p.z());
    if (sines < 0)
        return odd->value(u, v, p);
    else
        return even->value(u, v, p);
}
