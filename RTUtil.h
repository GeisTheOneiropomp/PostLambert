#pragma once
#include <cmath>
#include <limits>
#include <memory>
#include <random>
#include "ray.h"

// Usings

namespace rt_math {
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
        static std::random_device rd;  //Will be used to obtain a seed for the random number engine
        static std::uniform_real_distribution<double> distribution(0.0, 1.0);
        static std::mt19937 generator(rd());
        return distribution(generator);
    }

    inline double RandomDouble(double min, double max) {
        return min + (max - min) * RandomDouble();
    }

    inline double WeightedLinearDouble(double sample) {
        return sqrt(sample);
    }

    inline double WeightedCubicDouble(double sample) {
        return pow(sample, 3);
    }

    inline double WeightedExponential(double sample, int power) {
        return pow(sample, power);
    }

    inline int RandomInt(int min, int max) {
        return static_cast<int>(RandomDouble(min, max + 1));
    }

    inline double Clamp(double x, double min, double max) {
        if (x < min) return min;
        if (x > max) return max;
        return x;
    }
}

