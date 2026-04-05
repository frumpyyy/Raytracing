#pragma once

#ifndef MATH_CONSTANTS_H
#define MATH_CONSTANTS_H

#include <cmath>

#include <cstdlib>

#include <iostream>

#include <limits>

#include <memory>

#include <random>

#include <thread>

using std::make_shared;

using std::shared_ptr;

//constants 

const double infinity = std::numeric_limits<double>::infinity();

const double pi = 3.1415926535897932385;

//utility functions

inline double deg2rad(double degrees) {
	return degrees * pi / 180.0;
}

inline double random_double() {
	thread_local std::mt19937 generator(
		std::random_device{}() ^
		static_cast<unsigned>(std::hash<std::thread::id>{}(std::this_thread::get_id()))
	);
	thread_local std::uniform_real_distribution<double> distribution(0.0, 1.0);
	return distribution(generator);
}

inline double random_double(double min, double max) {
	return min + (max - min) * random_double();
}


#endif // !MATH_CONSTANTS_H
