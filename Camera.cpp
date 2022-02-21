#include "Camera.h"
#include <math.h>
using namespace rt_math;

//50 mm camera
// aperture 
Camera::Camera(Point3 lookFrom, Point3 lookAt, Vec3 upVec, double verticalFieldOfView,
    double aspectRatio, double aperture, double focusDistance) {

    auto theta = DegreesToRadians(verticalFieldOfView);
    auto height = tan(theta/2);
    auto viewportHeight = 2.0 * height;
    auto viewportWidth = aspectRatio * viewportHeight;

    w = UnitVector(lookFrom - lookAt);
    u = UnitVector(Cross(upVec, w));
    v = Cross(w, u);

    origin = lookFrom;
    lensCenter = lookAt;
    horizontal = focusDistance * viewportWidth * u;
    vertical = focusDistance * viewportHeight * v;
    lowerLeftCorner = origin - horizontal / 2 - vertical / 2 - focusDistance*w;
    lensRadius = aperture / 2;
}

Ray Camera::getRay(double s, double t) const
{
    Vec3 rd = lensRadius * RandomInUnitDisk();
    Vec3 offset = u * rd.x() + v * rd.y();
    return Ray(origin + offset, 
        lowerLeftCorner + (s * horizontal) + (t * vertical) - origin - offset);
}