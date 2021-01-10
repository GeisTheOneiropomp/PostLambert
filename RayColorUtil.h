#pragma once
#include "Ray.h"
#include "Hittable.h"
#include "RTWeekendUtil.h"
Color RayColor(const Ray& r, const Hittable& world, int depth);
Color RayColorWithBackground(const Ray& ray, const Color& background, const Hittable& world, int depth);

