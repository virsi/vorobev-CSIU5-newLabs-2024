#include "Functions.h"
#include <cmath>

double f1(double x) {
    return x;
}

double f2(double x) {
    return std::sin(22 * x);
}

double f3(double x) {
    return x * x * x * x;
}

double f4(double x) {
    return std::atan(x);
}
