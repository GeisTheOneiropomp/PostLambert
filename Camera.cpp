#include "Camera.h"

Camera::Camera() {
    auto kAspectRatio = 16.0 / 9.0;
    auto kViewportHeight = 2.0;
    auto kViewportWidth = kAspectRatio * kViewportHeight;
    auto focalLength = 1.0;

    origin = Point3(0, 0, 0);
    horizontal = Vec3(kViewportWidth, 0, 0);
    vertical = Vec3(0, kViewportHeight, 0);
    lowerLeftCorner = origin - horizontal / 2 - vertical / 2 - Vec3(0, 0, focalLength);
}

Ray Camera::getRay(double u, double v) const
{
    return Ray(origin, lowerLeftCorner + u * horizontal + v * vertical - origin);
}
