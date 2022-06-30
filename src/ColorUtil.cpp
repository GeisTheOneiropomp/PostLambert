#include "ColorUtil.h"
#include "rtutil.h"
#include "../extern/EasyBMP/EasyBMP.h"
using namespace rt_math;
namespace ColorUtil {
	void ColorUtil::WriteColor(Color pixel_color, int samplesPerPixel, BMP* outputImage, int x, int y)
	{
		auto r = pixel_color.x();
		auto g = pixel_color.y();
		auto b = pixel_color.z();

		// Divide the color by the number of samples.
		auto scale = 1.0 / samplesPerPixel;
		r = sqrt(scale * r);
		g = sqrt(scale * g);
		b = sqrt(scale * b);

		RGBApixel color;
		color.Red = (int)(256 * Clamp(r, 0.0, 0.999));
		color.Blue = (int)(256 * Clamp(b, 0.0, 0.999));
		color.Green = (int)(256 * Clamp(g, 0.0, 0.999));
		outputImage->SetPixel(x, y, color);
	}
}