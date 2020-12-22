#include "Vec3Util.h"

inline std::ostream& Vec3Util::operator<<(std::ostream& out, const Vec3& v)
{
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline Vec3 Vec3Util::operator+(const Vec3& u, const Vec3& v)
{
    return Vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

Vec3 Vec3Util::operator-(const Vec3& u, const Vec3& v)
{
    return Vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

Vec3 Vec3Util::operator*(const Vec3& u, const Vec3& v)
{
    return Vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

Vec3 Vec3Util::operator/(const Vec3 u, double t)
{
    return (1 / t) * u;
}

Vec3 Vec3Util::operator*(double t, const Vec3& v)
{
    return Vec3(v.e[0] * t, v.e[1] * t, v.e[2] * t);
}

double Vec3Util::dot(const Vec3& u, const Vec3& v)
{
    return  u.e[0] * v.e[0] + 
            u.e[1] * v.e[1] + 
            u.e[2] * v.e[2];
}

Vec3 Vec3Util::cross(const Vec3& u, const Vec3& v)
{
    return Vec3(
        u.e[1] * v.e[2] - u.e[2] * v.e[1],
        u.e[2] * v.e[0] - u.e[0] * v.e[2],
        u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

Vec3 Vec3Util::unit_vector(Vec3 u)
{
    return u / u.Length();
}

Vec3 Vec3Util::operator*(const Vec3 u, double t)
{
    return Vec3();
}