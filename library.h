#ifndef LIBRARY_H
#define LIBRARY_H

#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>

const double Infinity = std::numeric_limits<double>::infinity();
const double PI = 3.1415926535897932385;

inline double degrees_to_radians(double degrees)
{
    return degrees * PI / 180;
}
inline double min_z(double a, double b) { return a <= b ? a : b;}
inline double max_z(double a, double b) { return a >= b ? a : b;}
inline double clamp(double x, double min, double max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

inline double random_double() {
    return rand() / (RAND_MAX + 1.0);
}

inline double random_double(double min, double max) {
    return min + (max-min)*random_double();
}

#endif