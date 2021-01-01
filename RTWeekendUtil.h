#pragma once
#include <cmath>
#include <limits>
#include <memory>
#include <random>
#include "ray.h"

// Usings

namespace rtweekend_math {
    using std::shared_ptr;
    using std::make_shared;
    using std::sqrt;

    // Constants

    const double infinity = std::numeric_limits<double>::infinity();
    const double pi = 3.1415926535897932385;

    // Utility Functions

    inline double DegreesToRadians(double degrees) {
        return degrees * pi / 180.0;
    }

    inline double RandomDouble() {
        static std::uniform_real_distribution<double> distribution(0.0, 1.0);
        static std::mt19937 generator;
        return distribution(generator);
    }

    inline double RandomDouble(double min, double max) {
        // Returns a random real in [min,max).
        return min + (max - min) * RandomDouble();
    }

    inline double Clamp(double x, double min, double max) {
        if (x < min) return min;
        if (x > max) return max;
        return x;
    }
}

