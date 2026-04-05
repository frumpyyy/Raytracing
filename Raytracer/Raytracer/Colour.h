#pragma once

#ifndef COLOUR_H
#define COLOUR_H

#include "Interval.h"

#include "Vector3.h"

#include <iostream>

using colour = Vector3;

void WriteColour(std::ostream& out, const colour& pixel_colour) {
	auto r = pixel_colour.x();
	auto g = pixel_colour.y();
	auto b = pixel_colour.z();

	//scaling the 0 -> 1 values of x,y,z to byte range of 0 -> 255
	static const interval intensity(0.000, 0.999);
	int rB = int(256 * intensity.clamp(r));
	int gB = int(256 * intensity.clamp(g));
	int bB = int(256 * intensity.clamp(b));

	out << rB << ' ' << gB << ' ' << bB << '\n';
}


#endif 
