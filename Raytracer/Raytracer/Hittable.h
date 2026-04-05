#pragma once

#ifndef HITTABLE_H
#define HITTABLE_H

#include "MathConstants.h"


class hit_record {
public:
	point3 m_point;
	Vector3 m_normal;
	double t;
	bool frontFacing;

	void setFaceNormal(const Ray& r, const Vector3& outFacingNormal) {
		frontFacing = Dot(r.direction(), outFacingNormal) < 0;
		m_normal = frontFacing ? outFacingNormal : -outFacingNormal;
	}
};

class hittable {
public:
	virtual ~hittable() = default;

	virtual bool hit(const Ray& r, interval ray_t, hit_record& rec)const = 0;
};


#endif // !HITTABLE_H
