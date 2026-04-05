#pragma once

#ifndef COLOUR_H
#define COLOUR_H

#include "Vector3.h"

#include <iostream>

using colour = Vector3;

void WriteColour(std::ostream& out, const colour& pixel_colour) {
	auto r = pixel_colour.x();
	auto g = pixel_colour.y();
	auto b = pixel_colour.z();

	//scaling the 0 -> 1 values of x,y,z to byte range of 0 -> 255
	int rB = int(255.999 * r);
	int gB = int(255.999 * g);
	int bB = int(255.999 * b);

	out << rB << ' ' << gB << ' ' << bB << '\n';
}


#endif 
