#pragma once
#include "Ray.h"
#include "Hittable.h"
#include "RTUtil.h"
#include "Skybox.h"
Color RayColor(const Ray& r, const Hittable& world, int depth);
Color RayColorWithBackground(const Ray& ray, const Skybox* skybox, const Hittable& world, int depth);

