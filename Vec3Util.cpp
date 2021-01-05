#include "Vec3Util.h"
#include "RTWeekendUtil.h"

using namespace rtweekend_math;

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

    Vec3 operator*(const Vec3 u, double t)
    {
        return Vec3(u.e[0] * t, u.e[1] * t, u.e[2] * t);
    }

    double Dot(const Vec3& u, const Vec3& v)
    {
        return  u.e[0] * v.e[0] +
            u.e[1] * v.e[1] +
            u.e[2] * v.e[2];
    }

    Vec3 Cross(const Vec3& u, const Vec3& v)
    {
        return Vec3(
            u.e[1] * v.e[2] - u.e[2] * v.e[1],
            u.e[2] * v.e[0] - u.e[0] * v.e[2],
            u.e[0] * v.e[1] - u.e[1] * v.e[0]);
    }

    Vec3 UnitVector(Vec3 u)
    {
        return u / u.Length();
    }

    Vec3 random()
    {
        return Vec3(RandomDouble(), RandomDouble(), RandomDouble());
    }

    Vec3 random(double min, double max)
    {
        return Vec3(RandomDouble(min, max), RandomDouble(min, max), RandomDouble(min, max));
    }

    Vec3 RandomInUnitSphere()
    {
        auto phi = RandomDouble(0, 2 * pi);
        auto costheta = RandomDouble(-1, 1);
        auto u = RandomDouble(0, 1);
        auto theta = acos(costheta);
        auto r = cbrt(u);
        return Vec3(r * sin(theta) * cos(phi), r * sin(theta) * sin(phi), r * cos(theta));
    }

    Vec3 RandomUnitVector() {
        return UnitVector(RandomInUnitSphere());
    }

    Vec3 RandomInHemisphere(const Vec3& normal) {
        Vec3 inUnitSphere = RandomInUnitSphere();
        return (Dot(inUnitSphere, normal) > 0.0) ? inUnitSphere : -inUnitSphere;
    }

    Vec3 RandomInUnitDisk() {
        auto theta = RandomDouble(0, 2*pi);
        auto r =  sqrt(RandomDouble(0, 1));
        return Vec3(cos(theta) * r, sin(theta) * r, 0);
    }

    Vec3 Reflect(const Vec3& v, const Vec3& normal)
    {
        return v - 2*Dot(v,normal) * normal;
    }

    Vec3 Refract(const Vec3& uv, const Vec3 normal, double etai_over_etat)
    {
        auto cos_theta = fmin(Dot(-uv, normal), 1.0);
        Vec3 r_out_perp = etai_over_etat * (uv + cos_theta * normal);
        Vec3 r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.LengthSquared())) * normal;
        return r_out_perp + r_out_parallel;
    }
