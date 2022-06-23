#include "PhaseFunctionsUtils.h"
#include <cmath>
#include "RTUtil.h"

using namespace rt_math;
double Isotropic()
{
    return 1.0;
}

double Rayleigh(const double phase_angle)
{
    return .75 * (1 + cos(phase_angle) * cos(phase_angle));
}

double LegendrePolynomial(const int order, const double phase_angle, const double b_1 = 1, const double b_2 = 0)
{
    if (order == 1) {
        return 1 + b_1 * cos(phase_angle);
    }
    else if (order == 2) {
        return 1 + b_1 * cos(phase_angle) + b_2 * ((3 * cos(phase_angle * phase_angle) - 1));
    }
    return 0.0;
}

double OneTermHenyeyGreenstein(const double asymmetry_factor, const double phase_angle)
{
    auto numerator = (1 - (asymmetry_factor * asymmetry_factor));
    auto denominator = pow((1 - (2 * asymmetry_factor * cos(phase_angle)) + asymmetry_factor * asymmetry_factor), 3/2);
    return numerator / denominator;
}

double cot(const double i) {
    return cos(i) / sin(i);
}

double HapkeF(const double psi)
{
    return exp(-2 * tan(psi/2));
}

double HapkeChi(const double theta)
{
    return 1/(pow(.5,(1 + pi * pow(2, tan(theta)))));
}

double HapkeE1(const double theta, const double y)
{
    return exp((-2/pi) * cot(theta) * cot(y));
}

double HapkeE2(const double theta, const double y)
{
    return exp((-1/pi) * pow(2, cot(theta)) * pow(2, cot(y)));
}

double HapkeEta(const double theta, const double y)
{
    return HapkeChi(theta) * (cos(y) + sin(y)*tan(theta)*(HapkeE2(theta, y) / (2 - HapkeE1(theta, y))));
}

double HapkeMuNaught1(const double theta, const double i, const double e, const double psi)
{
    return HapkeChi(theta) * (cos(i) + (sin(i) * tan(theta) * (cos(psi) * HapkeE2(theta, e) +
        pow(2, sin(psi/2)) * HapkeE2(theta, i)) / (2 - HapkeE1(theta, e) - (psi/pi) * HapkeE1(theta, i))));
}

double HapkeMu1(const double theta, const double i, const double e, const double psi)
{
    return HapkeChi(theta) * (cos(e) + (sin(e) * tan(theta) * (HapkeE2(theta, e) - pow(2, sin(psi/2)) *
        HapkeE2(theta, i)) / (2 - HapkeE1(theta, e) - (psi / pi) * HapkeE1(theta, i))));
}

// psi is the azimuth angle between the source and the detector planes
// i is the angle of incidence
// e is the angle of emergence
double HapkeShadowing1(const double theta, const double i, const double e, const double psi)
{
    return (HapkeMu1(theta, i, e, psi) / (HapkeEta(theta, e))) * 
        (HapkeMuNaught1(theta, i, e, psi) / HapkeEta(theta, i)) *
        (HapkeChi(theta) / (1 - HapkeF(psi) + (HapkeF(psi) * HapkeChi(theta) * (HapkeMuNaught1(theta, i, e, psi) / HapkeEta(theta,i)))));
}

double HapkeMuNaught2(const double theta, const double i, const double e, const double psi)
{
    return HapkeChi(theta) * (cos(i) + (sin(i) * tan(theta) * (HapkeE2(theta, i) -
        pow(2, sin(psi / 2)) * HapkeE2(theta, e)) / (2 - HapkeE1(theta, i) - (psi / pi) * HapkeE1(theta, e))));
}

double HapkeMu2(const double theta, const double i, const double e, const double psi)
{
    return HapkeChi(theta) * (cos(e) + (sin(e) * tan(theta) * (HapkeE2(theta, e) - pow(2, sin(psi / 2)) *
        HapkeE2(theta, i)) / (2 - HapkeE1(theta, e) - (psi / pi) * HapkeE1(theta, i))));
}

double HapkeShadowing2(const double theta, const double i, const double e, const double psi)
{
    return (HapkeMu2(theta, i, e, psi) / (HapkeEta(theta, e))) * 
        (HapkeMuNaught2(theta, i, e, psi) / HapkeEta(theta, i)) *
        (HapkeChi(theta) / (1 - HapkeF(psi) + (HapkeF(psi) * HapkeChi(theta) * (HapkeMu2(theta, i, e, psi) / HapkeEta(theta, e)))));
}
