#pragma once

#ifndef RAY_H
#define RAY_H

#include "Vector3.h"

class Ray {
public:
	Ray() {}

	Ray(const point3& origin, const Vector3& direction) : _origin(origin), _direction(direction) {}

	const point3& origin() const { return _origin; }
	const Vector3& direction() const { return _direction; }

	point3 at(double t) const {
		return _origin + t * _direction;
	}

private:
	point3 _origin;
	Vector3 _direction;

};


#endif 
