#pragma once
#include <cmath>

const double EPS = 1e-9;

bool tolerant_eq(double a, double b){ return abs(a - b) < EPS; }

