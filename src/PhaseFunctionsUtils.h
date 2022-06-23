#pragma once
double Isotropic();
double Rayleigh(const double phase_angle);
double LegendrePolynomial(const int order, const double phase_angle, const double b_1, const double b_2);
double OneTermHenyeyGreenstein(const double asymmetry_factor, const double phase_angle);

double HapkeF(const double psi);
double HapkeChi(const double theta);
double HapkeE1(const double theta, const double y);
double HapkeE2(const double theta, const double y);
double HapkeEta(const double theta, const double y);
double HapkeMuNaught1(const double theta, const double i, const double e, const double psi);
double HapkeMu1(const double theta, const double i, const double e, const double psi);
double HapkeShadowing1(const double theta, const double i, const double e, const double psi);
double HapkeMuNaught2(const double theta, const double i, const double e, const double psi);
double HapkeMu2(const double theta, const double i, const double e, const double psi);
double HapkeShadowing2(const double theta, const double i, const double e, const double psi);