#include "Camera.h"
#include <math.h>
using namespace rtweekend_math;

Camera::Camera(Point3 lookFrom, Point3 lookAt, Vec3 upVec, double verticalFieldOfView,
    double aspectRatio, double aperture, double focusDistance,
    double time0, double time1, double tilt, double shift) {

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
    this->time0 = time0;
    this->time1 = time1; 
    this->tilt = tilt;
    this->shift = shift;
}

Ray Camera::getRay(double s, double t) const
{
    Vec3 rd = lensRadius * RandomInUnitDisk();
    Vec3 offset = u * rd.x() + v * rd.y();
    return Ray(origin + offset, 
        lowerLeftCorner + (s * (horizontal + Vec3(shift, 0, 0))) + (t * vertical + Vec3(0, tilt, 0)) - origin - offset, 
        RandomDouble(time0, time1));
}


double Camera::vignetteFactor(double s, double t) const {
    Vec3 opticalAxis = lensCenter - origin;
    Vec3 chiefRay =  lensCenter - (lowerLeftCorner + (s * (horizontal + Vec3(shift, 0, 0)) + (t * (vertical + Vec3(0, tilt, 0)))));
    auto returnThis = pow(CosAngle(opticalAxis, chiefRay), 4);
    return pow(CosAngle(opticalAxis, chiefRay), 4);
}
