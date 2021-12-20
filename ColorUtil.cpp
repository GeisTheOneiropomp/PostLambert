#include "ColorUtil.h"
#include "rtutil.h"
using namespace rt_math;
namespace ColorUtil {
	void ColorUtil::WriteColor(std::ostream& out, Color pixel_color, int samplesPerPixel)
	{
		auto r = pixel_color.x();
		auto g = pixel_color.y();
		auto b = pixel_color.z();

		// Divide the color by the number of samples.
		auto scale = 1.0 / samplesPerPixel;
		r = sqrt(scale * r);
		g = sqrt(scale * g);
		b = sqrt(scale * b);

		out << static_cast<int>(256 * Clamp(r, 0.0, 0.999)) << ' '
			<< static_cast<int>(256 * Clamp(g, 0.0, 0.999)) << ' '
			<< static_cast<int>(256 * Clamp(b, 0.0, 0.999)) << '\n';
	}
}