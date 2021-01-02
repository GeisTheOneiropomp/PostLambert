#pragma once
#include "Ray.h"
#include "Hittable.h"
#include "RTWeekendUtil.h"
Color RayColor(const Ray& r, const Hittable& world, int depth);

