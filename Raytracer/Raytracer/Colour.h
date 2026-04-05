#pragma once

#ifndef COLOUR_H
#define COLOUR_H

#include "Interval.h"

#include "Vector3.h"

#include <iostream>

#include <string>

using colour = Vector3;

inline double linearToGamma(double linearComponent) {
	if (linearComponent > 0)
		return std::sqrt(linearComponent);

	return 0;
}

inline void WriteColour(std::string& out, const colour& pixel_colour) {
	auto r = pixel_colour.x();
	auto g = pixel_colour.y();
	auto b = pixel_colour.z();

	r = linearToGamma(r);
	g = linearToGamma(g);
	b = linearToGamma(b);

	//scaling the 0 -> 1 values of x,y,z to byte range of 0 -> 255
	static const interval intensity(0.000, 0.999);
	int rB = int(256 * intensity.clamp(r));
	int gB = int(256 * intensity.clamp(g));
	int bB = int(256 * intensity.clamp(b));

	char buf[32];
	int len = std::snprintf(buf, sizeof(buf), "%d %d %d\n", rB, gB, bB);
	out.append(buf, len);
}


#endif 
