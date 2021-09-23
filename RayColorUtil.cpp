#include "RayColorUtil.h"
#include "math.h"
#include "ImageTexture.h"
#include "MonochromaticRay.h"
#include "Diffraction.h"

Color RayColor(const Ray& ray, const Hittable& world, int depth) {

    if (depth == 0) {
        return Color(0, 0, 0);
    }
    HitRecord record;

    if (world.Hit(ray, 0.001, rtweekend_math::infinity, record)) {
        Ray scattered;
        Color attenuation;
        if (record.material_pointer->scatter(ray, record, attenuation, scattered)) {
            return attenuation * RayColor(scattered, world, depth - 1);
        }
        return Color(0, 0, 0);
    }

    Vec3 unit_direction = UnitVector(ray.direction());
    auto t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
}

Color RayColorWithBackground(const Ray& ray, const Skybox* skybox, const Hittable& world, int depth) {

    if (depth == 0) {
        return Color(0, 0, 0);
    }
    HitRecord record;

    if (!world.Hit(ray, 0.001, rtweekend_math::infinity, record)) 
    {
        auto direction = ray.direction();
        return skybox->getValue(ray.direction());
    }

    Ray scattered;
    Color attenuation;
    Color emitted = record.material_pointer->emitted(record.u_coord, record.v_coord, record.point);

    if (!record.material_pointer->scatter(ray, record, attenuation, scattered)) {
        return emitted;
    }

    return emitted + attenuation * RayColorWithBackground(scattered, skybox, world, depth - 1);

}

Color DiffractionRayColorWithBackground(const MonochromaticRay& mray, const Skybox* skybox, const Hittable& world, int depth) {
    
    if (depth == 0) {
        return Color(0, 0, 0);
    }
    HitRecord record;

    auto testVar = mray.intensity * WavelengthToRGB(mray.wavelength);

    Ray scattered;
    Color attenuation;
    auto diffIntensityFactor = mray.intensity * UnitVector(WavelengthToRGB(mray.wavelength));
    auto rayTraceValue = (diffIntensityFactor * RayColorWithBackground(mray.ray, skybox, world, depth - 1));
    return rayTraceValue;

}

Color WavelengthToRGB(double wavelength) {
    if ((wavelength >= 380) && (wavelength < 440)) {
        return Color( -(wavelength - 440) / (440-380),0.0,1.0);
    }
    else if ((wavelength >= 440) && (wavelength < 490)) {
        return Color(0.0, (wavelength - 440.0) / (490.0 - 440.0), 1.0);
    }
    else if ((wavelength >= 490) && (wavelength < 510)) {
        return Color(0.0, 1.0, -(wavelength - 510.0) / (510.0 - 490.0));
    }
    else if ((wavelength >= 510) && (wavelength < 580)) {
        return Color((wavelength - 510.0) / (580.0 - 510.0), 1.0, 0.0);
    }
    else if ((wavelength >= 580) && (wavelength < 645)) {
        return Color(1.0, -(wavelength - 645.0) / (645.0 - 580.0), 0.0);
    }
    else if ((wavelength >= 645) && (wavelength < 781)) {
        return Color(1.0, 0.0, 0.0);
    }
    else {
        return Color(0.0, 0.0, 0.0);
    }
}