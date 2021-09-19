#include "Camera.h"

using namespace rtweekend_math;

Camera::Camera(Point3 lookFrom, Point3 lookAt, Vec3 upVec, double verticalFieldOfView,
    double aspectRatio, double aperture, double focusDistance,
    double time0, double time1) {

    auto theta = DegreesToRadians(verticalFieldOfView);
    auto height = tan(theta/2);
    auto viewportHeight = 2.0 * height;
    auto viewportWidth = aspectRatio * viewportHeight;

    w = UnitVector(lookFrom - lookAt);
    u = UnitVector(Cross(upVec, w));
    v = Cross(w, u);

    origin = lookFrom;
    horizontal = focusDistance * viewportWidth * u;
    vertical = focusDistance * viewportHeight * v;
    lowerLeftCorner = origin - horizontal / 2 - vertical / 2 - focusDistance*w;
    lensRadius = aperture / 2;
    this->time0 = time0;
    this->time1 = time1; // TODO: Refactor?
}

Ray Camera::getRay(double s, double t) const
{
    Vec3 rd = lensRadius * RandomInUnitDisk();
    Vec3 offset = u * rd.x() + v * rd.y();
    return Ray(origin + offset, 
        lowerLeftCorner + s * horizontal + t * vertical - origin - offset, RandomDouble(time0, time1));
}
