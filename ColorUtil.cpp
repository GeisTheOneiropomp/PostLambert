#include "ColorUtil.h"
#include "RTWeekendUtil.h"
namespace ColorUtil {
	void ColorUtil::WriteColor(std::ostream& out, Color pixel_color, int samplesPerPixel)
	{
		auto r = pixel_color.x();
		auto g = pixel_color.y();
		auto b = pixel_color.z();

		// Divide the color by the number of samples.
		auto scale = 1.0 / samplesPerPixel;
		r *= scale;
		g *= scale;
		b *= scale;

		out << static_cast<int>(256 * clamp(r, 0.0, 0.999)) << ' '
			<< static_cast<int>(256 * clamp(g, 0.0, 0.999)) << ' '
			<< static_cast<int>(256 * clamp(b, 0.0, 0.999)) << '\n';
	}
}