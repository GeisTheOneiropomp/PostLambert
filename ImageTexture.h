#pragma once
#include "Texture.h"
#include <algorithm>
#include <iostream>
#include "RTWeekendUtil.h"
class ImageTexture : public Texture
{
public:
    const static int bytes_per_pixel = 3;

    ImageTexture();
    ImageTexture(const char* filename);
    ~ImageTexture();

    virtual Color value(double u, double v, const Vec3& p) const override;
  
private:
    unsigned char* data;
    int width, height;
    int bytes_per_scanline;

};

