#include "ColorUtil.h"
namespace ColorUtil {
	void ColorUtil::WriteColor(std::ostream& out, Color pixel_color)
	{
		out << static_cast<int>(255.999 * pixel_color.x()) << ' '
			<< static_cast<int>(255.999 * pixel_color.y()) << ' '
			<< static_cast<int>(255.999 * pixel_color.z()) << '\n';
	}
}