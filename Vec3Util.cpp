#include "Vec3Util.h"
#include "RTWeekendUtil.h"

namespace Vector3Namespace 
{

    std::ostream& operator<<(std::ostream& out, const Vec3& v)
    {
        return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
    }

    Vec3 operator+(const Vec3& u, const Vec3& v)
    {
        return Vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
    }

    Vec3 operator-(const Vec3& u, const Vec3& v)
    {
        return Vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
    }

    Vec3 operator*(const Vec3& u, const Vec3& v)
    {
        return Vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
    }

    Vec3 operator/(const Vec3 u, double t)
    {
        return (1 / t) * u;
    }

    Vec3 operator*(double t, const Vec3& v)
    {
        return Vec3(v.e[0] * t, v.e[1] * t, v.e[2] * t);
    }

    double dot(const Vec3& u, const Vec3& v)
    {
        return  u.e[0] * v.e[0] +
            u.e[1] * v.e[1] +
            u.e[2] * v.e[2];
    }

    Vec3 cross(const Vec3& u, const Vec3& v)
    {
        return Vec3(
            u.e[1] * v.e[2] - u.e[2] * v.e[1],
            u.e[2] * v.e[0] - u.e[0] * v.e[2],
            u.e[0] * v.e[1] - u.e[1] * v.e[0]);
    }

    Vec3 unit_vector(Vec3 u)
    {
        return u / u.Length();
    }

    Vec3 operator*(const Vec3 u, double t)
    {
        return Vec3(u.e[0] * t, u.e[1] * t, u.e[2] * t);
    }

    Vec3 random()
    {
        return Vec3(random_double(), random_double(), random_double());
    }

    Vec3 random(double min, double max)
    {
        return Vec3(random_double(min, max), random_double(min, max), random_double(min, max));
    }

    Vec3 randomInUnitSphere()
    {
        while (true) {
            auto p = random(-1, 1);
            if (p.LengthSquared() >= 1) continue;
            return p;
        }
    }

    Vec3 randomUnitVector() {
        return unit_vector(randomInUnitSphere());
    }

    Vec3 randomInHemisphere(const Vec3& normal) {
        Vec3 inUnitSphere = randomInUnitSphere();
        if (dot(inUnitSphere, normal) > 0.0) // In the same hemisphere as the normal
            return inUnitSphere;
        else
            return -inUnitSphere;
    }

    Vec3 reflect(const Vec3& v, const Vec3& normal)
    {
        return v - 2*dot(v,normal) * normal;
    }

}