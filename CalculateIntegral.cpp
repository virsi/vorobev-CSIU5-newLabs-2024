#include <iostream>
#include <cmath>
#include <iomanip>

#include "CalculateIntegral.h"

double IntRect(TPF f, double a, double b, int n) {
    double h = (b - a) * 1.0 / n;
    double result = 0.0;

    for (int i = 0; i < n; i++)
        result += f(a + h * (i + 0.5));

    result *= h;

    return result;
}

double IntTrap(TPF f, double a, double b, int n) {
    double width = (b - a) * 1.0 / n;
    double trapezoidal_integral = 0;
    double x1, x2, h;

    for (int step = 0; step < n; step++) {
        x1 = a + step * width;
        x2 = a + (step + 1) * width;
        h = x2 - x1;

        trapezoidal_integral += 0.5 * h * (f(x1) + f(x2));
    }

    return trapezoidal_integral;
}

double Integrate(TPF f, TPM method, double a, double b, double eps, int &n) {
    n = 2;
    int i = 0;
    double diff;
    do {
        i++;
        diff = method(f, a, b, n * i) - method(f, a, b, n * (i + 1));
    } while (std::abs(diff)/3 > eps);
    n = n * (i + 1);
    return method(f, a, b, n * i);
}
