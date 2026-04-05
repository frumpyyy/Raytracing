#pragma once

#ifndef MATERIAL_H
#define MATERIAL_H

#include "Ray.h"

#include "Colour.h"

#include "Vector3.h"

class hit_record;

class material {
public:
	virtual ~material() = default;

	virtual bool scatter(const Ray& r_in, const hit_record& rec, colour& attenuation, Ray& scattered)const { return false; }

};

class lambertian : public material {
public:
	lambertian(const colour& albedo) : _albedo(albedo) {}

	bool scatter(const Ray& r_in, const hit_record& rec, colour& attenuation, Ray& scattered) const override
	{
		auto scatter_direction = rec.m_normal + RandomUnitVector();

		if (scatter_direction.NearZero())
			scatter_direction = rec.m_normal;

		scattered = Ray(rec.m_point, scatter_direction);
		attenuation = _albedo;
		return true;
	}

private:
	colour _albedo;
};

class metal : public material {
public:
	metal(const colour& albedo) : _albedo(albedo) {}

	bool scatter(const Ray& r_in, const hit_record& rec, colour& attenuation, Ray& scattered)
		const override {
		Vector3 reflected = reflect(r_in.direction(), rec.m_normal);
		scattered = Ray(rec.m_point, reflected);
		attenuation = _albedo;
		return true;
	}

private:
	colour _albedo;
};

#endif // !MATERIAL_H
