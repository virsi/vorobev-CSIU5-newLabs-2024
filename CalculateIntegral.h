#pragma once

typedef double (*TPF)(double);
typedef double (*TPM)(TPF f, double a, double b, int n);
double IntRect(TPF f, double a, double b, int n);
double IntTrap(TPF f, double a, double b, int n);
double Integrate(TPF f, TPM method, double a, double b, double eps, int &n);