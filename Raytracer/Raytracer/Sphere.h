#pragma once

#ifndef SPHERE_H
#define SPHERE_H

#include "Hittable.h"

#include "MathConstants.h"

class sphere : public hittable {
public:
	sphere(const point3& center, double radius) : _center(center), _radius(std::fmax(0, radius)) {}

	bool hit(const Ray& r, interval ray_t, hit_record& rec)const override {
		Vector3 oc = _center - r.origin();
		double a = r.direction().LengthSquared();
		double h = Dot(r.direction(), oc);
		double c = oc.LengthSquared() - _radius * _radius;
		double discriminant = h * h - a * c;

		//no hit case
		if (discriminant < 0)
			return false;

		double sqrtDiscriminant = std::sqrt(discriminant);

		double root = (h - sqrtDiscriminant) / a;
		if (!ray_t.surrounds(root)) {
			root = (h + sqrtDiscriminant) / a;
			if (!ray_t.surrounds(root))
				return false;
		}

		rec.t = root;
		rec.m_point = r.at(rec.t);
		Vector3 outNormal = (rec.m_point - _center) / _radius;
		rec.setFaceNormal(r, outNormal);

		return true;

	}


private:
	point3 _center;
	double _radius;
};




#endif // !SPHERE_H
