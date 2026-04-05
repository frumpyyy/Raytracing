#pragma once

#ifndef MATH_CONSTANTS_H
#define MATH_CONSTANTS_H

#include <cmath>

#include <iostream>

#include <limits>

#include <memory>

using std::make_shared;

using std::shared_ptr;

//constants 

const double infinity = std::numeric_limits<double>::infinity();

const double pi = 3.1415926535897932385;

//utility functions

inline double deg2rad(double degrees) {
	return degrees * pi / 180.0;
}

//common headers

#include "colour.h"

#include "Interval.h"

#include "Ray.h"

#include "Vector3.h"


#endif // !MATH_CONSTANTS_H
