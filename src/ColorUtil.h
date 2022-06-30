#pragma once
#include "vec3.h"
#include <iostream>
#include "../extern/EasyBMP/EasyBMP.h"

namespace ColorUtil {
	void WriteColor(Color pixel_color, int samplesPerPixel, BMP* outputImage, int x, int y);
}
 