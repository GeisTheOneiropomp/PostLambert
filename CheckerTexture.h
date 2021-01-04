#pragma once
#include "Texture.h"
#include "Hittable.h"
#include "SolidColor.h"

#include <memory>
using std::shared_ptr;

class CheckerTexture :
    public Texture
{
public:
    CheckerTexture();
    CheckerTexture(shared_ptr<Texture> even, shared_ptr<Texture> odd);
    CheckerTexture(Color c1, Color c2);
    virtual Color value(double u, double v, const Point3& p) const override;

private:
    shared_ptr<Texture> odd;
    shared_ptr<Texture> even;

};

