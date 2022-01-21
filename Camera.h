#pragma once
#include "rtutil.h"
#include "vec3.h"
#include "Vec3Util.h"
#include "Ray.h"
#include "MonochromaticRay.h"

using namespace Vector3Namespace;
class Camera
{
public:
    Camera(Point3 lookFrom, Point3 lookAt, Vec3 upVec, double fieldOfView, 
        double aspectRatio, double aperture, double focusDistance,
        double time0, double time1, double tilt, double shift, double baseTilt, double baseShift, bool useVignette);

    Ray getRay(double u, double v) const;
    MonochromaticRay getDiffractionRay(double s, double t, double wavelength) const;
    double vignetteFactor(double s, double t) const;

    double interpolateTilt(double randomVar) const;
    double interpolateShift(double randomVar) const;


private:
    Point3 origin;
    Point3 lensCenter;
    Point3 lowerLeftCorner;
    Vec3 horizontal;
    Vec3 vertical;
    Vec3 u, v, w;
    double lensRadius;
    double time0, time1;
    double tilt0, shift0;
    double tilt1, shift1;
    bool vignetteOption;

    double getDiffractionIntensity(double theta, double waveLength) const;

};

