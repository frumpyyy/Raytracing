#pragma once

#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "Hittable.h"

#include "MathConstants.h"

#include <vector>

using std::make_shared;
using std::shared_ptr;

class hittable_list : public hittable {
public:

	std::vector<shared_ptr<hittable>> objects;

	hittable_list() {}
	hittable_list(shared_ptr<hittable> object) { add(object); }

	void clear() { objects.clear(); }

	void add(shared_ptr<hittable> object) {
		objects.push_back(object);
	}

	bool hit(const Ray& r, interval ray_t, hit_record& rec) const override {
		hit_record temp_record;
		bool hitFound = false;
		double closest_hit = ray_t.max;

		for (const auto& object : objects) {
			if (object->hit(r, interval(ray_t.min, closest_hit), temp_record)) {
				hitFound = true;
				closest_hit = temp_record.t;
				rec = temp_record;
			}
		}

		return hitFound;

	}

};



#endif // !HITTABLE_LIST_H
