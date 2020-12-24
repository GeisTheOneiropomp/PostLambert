#include "Camera.h"

Camera::Camera(Point3 lookFrom, Point3 lookAt, Vec3 upVec, double verticalFieldOfView, double aspectRatio) {
    auto theta = degrees_to_radians(verticalFieldOfView);
    auto height = tan(theta/2);
    auto viewportHeight = 2.0 * height;
    auto viewportWidth = aspectRatio * viewportHeight;
    auto focalLength = 1.0;

    auto w = unit_vector(lookFrom - lookAt);
    auto u = unit_vector(cross(upVec, w));
    auto v = cross(w, u);

    origin = lookFrom;
    horizontal = viewportWidth * u;
    vertical = viewportHeight * v;
    lowerLeftCorner = origin - horizontal / 2 - vertical / 2 - w;
}

Ray Camera::getRay(double s, double t) const
{
    return Ray(origin, lowerLeftCorner + s * horizontal + t * vertical - origin);
}
