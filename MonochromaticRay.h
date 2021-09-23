#pragma once
#include "Ray.h"
namespace Vector3Namespace {
    class MonochromaticRay
    {
    public:
        MonochromaticRay();
        MonochromaticRay(const Point3& origin, const Vec3& direction, double time = 0.0, 
            double wavelength = 0.0, double intensity = 0.0);

        double wavelength;
        double intensity;
        Ray ray;
    };
}

