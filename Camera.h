#pragma once
#include "rtweekendutil.h"
#include "vec3.h"
#include "Vec3Util.h"
#include "Ray.h"
using namespace Vector3Namespace;
class Camera
{
public:
    Camera(Point3 lookFrom, Point3 lookAt, Vec3 upVec, double fieldOfView, 
        double aspectRatio, double aperture, double focusDistance);

    Ray getRay(double u, double v) const;

private:
    Point3 origin;
    Point3 lowerLeftCorner;
    Vec3 horizontal;
    Vec3 vertical;
    Vec3 u, v, w;
    double lensRadius;

};

