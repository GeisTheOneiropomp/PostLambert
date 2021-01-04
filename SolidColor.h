#pragma once
#include "Texture.h"
class SolidColor :
    public Texture
{
public:
    SolidColor();
    SolidColor(Color color);
    SolidColor(double red, double green, double blue);
    virtual Color value(double u, double v, const Vec3& p) const override;

private:
    Color color_value_;
};

