#include "Camera.h"
#include <math.h>
using namespace rt_math;

//50 mm camera
// aperture 
Camera::Camera(Point3 lookFrom, Point3 lookAt, Vec3 upVec, double verticalFieldOfView,
    double aspectRatio, double aperture, double focusDistance,
    double time0, double time1, double tilt0, double shift0, double tilt1, double shift1, bool useVignette) {

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
    this->tilt0 = tilt0;
    this->tilt1 = tilt1;
    this->shift0 = shift0;
    this->shift1 = shift1;
    this->vignetteOption = useVignette;
}

Ray Camera::getRay(double s, double t) const
{
    auto randomTime = WeightedExponential(RandomDouble(time0, time1), 5);
    auto randomTilt = interpolateTilt(randomTime);
    auto randomShift = interpolateShift(randomTime);
    Vec3 rd = lensRadius * RandomInUnitDisk();
    Vec3 offset = u * rd.x() + v * rd.y();
    return Ray(origin + offset, 
        lowerLeftCorner + (s * (horizontal + Vec3(randomShift, 0, 0))) + (t * vertical + Vec3(0, randomTilt, 0)) - origin - offset,
        randomTime);
}

MonochromaticRay Camera::getDiffractionRay(double s, double t, double wavelength) const {

    auto randomTime = WeightedExponential(RandomDouble(time0, time1), 5);
    auto randomTilt = interpolateTilt(randomTime);
    auto randomShift = interpolateShift(randomTime);
    Vec3 rd = lensRadius * RandomOnUnitDesk();
    Vec3 offset = u * rd.x() + v * rd.y();

    Vec3 actualOrgin = origin + offset;
    Vec3 opticalAxis = lensCenter - origin;
    Vec3 rayDirection = lowerLeftCorner + (s * (horizontal + Vec3(randomShift, 0, 0))) + (t * vertical + Vec3(0, randomTilt, 0)) - origin - offset;
    Vec3 chiefRay = -rayDirection;

    double diffAngle = Angle(opticalAxis, chiefRay);
    double intensity = getDiffractionIntensity(diffAngle, wavelength);
    return MonochromaticRay(origin + offset,
        lowerLeftCorner + (s * (horizontal + Vec3(randomShift, 0, 0))) + (t * vertical + Vec3(0, randomTilt, 0)) - origin - offset,
      randomTime, wavelength, intensity);

}

double Camera::getDiffractionIntensity(double theta, double wavelength) const {

    auto unitWavelength = wavelength * (0.000001);
    auto waveNumber = 2 * pi / unitWavelength;
    auto beta = (waveNumber * lensRadius / 50 * sin(theta));
    if (beta == 0.0f) {
        return 0.0;
    }
    return pow((sin(beta)/beta),2);
}

double Camera::vignetteFactor(double s, double t) const {

    if (vignetteOption) {
        auto randomTime = WeightedExponential(RandomDouble(time0, time1), 5);
        auto randomTilt = interpolateTilt(randomTime);
        auto randomShift = interpolateShift(randomTime);

        Vec3 opticalAxis = lensCenter - origin;
        Vec3 chiefRay = lensCenter - (lowerLeftCorner + (s * (horizontal + Vec3(randomShift, 0, 0)) + (t * (vertical + Vec3(0, randomTilt, 0)))));
        return pow(CosAngle(opticalAxis, chiefRay), 4);
    }
    else {
        return 1;
    }

}

double Camera::interpolateTilt(double randomVar) const {
   
    auto tiltDiff = tilt1 - tilt0;
    auto timeFactor = randomVar * (time1 - time0);
    return tilt0 + timeFactor* tiltDiff;

}

double Camera::interpolateShift(double randomVar) const {

    auto tiltDiff = shift1 - shift0;
    auto timeFactor = randomVar * (time1 - time0);
    return shift0 + timeFactor * tiltDiff;
}
