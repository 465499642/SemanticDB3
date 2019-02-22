#include "Sigmoids.h"

double clean(const double x) {
    if (x <= 0) { return 0.0; }
    return 1.0;
}

double threshold_filter(const double x, const double t) {
    if (x < t) { return 0.0;}
    return x;
}

double not_threshold_filter(const double x, const double t) {
    if (x <= t ) { return x; }
    return 0.0;
}

double binary_filter(const double x) {
    if (x <= 0.96) { return 0.0; }
    return 1.0;
}

double sigmoid_in_range(const double x, const double a, const double b) {
    if (a <= x && x <= b) { return x; }
    return 0.0;
}
