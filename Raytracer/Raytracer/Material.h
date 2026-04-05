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
	metal(const colour& albedo, double fuzz) : _albedo(albedo), _fuzz(fuzz < 1 ? fuzz : 1) {}

	bool scatter(const Ray& r_in, const hit_record& rec, colour& attenuation, Ray& scattered)
		const override {
		Vector3 reflected = reflect(r_in.direction(), rec.m_normal);
		reflected = UnitVector(reflected) + (_fuzz * RandomUnitVector());
		scattered = Ray(rec.m_point, reflected);
		attenuation = _albedo;
		return (Dot(scattered.direction(), rec.m_normal) > 0);
	}

private:
	colour _albedo;
	double _fuzz;
};

class dielectric : public material {
public:
	dielectric(double refractionIndex) : _refractionIndex(refractionIndex) {}

	bool scatter(const Ray& r_in, const hit_record& rec, colour& attenuation, Ray& scattered)
		const override {
		attenuation = colour(1.0, 1.0, 1.0);
		double ri = rec.frontFacing ? (1.0 / _refractionIndex) : _refractionIndex;
		Vector3 unit_direction = UnitVector(r_in.direction());
		double cos_theta = std::fmin(Dot(-unit_direction, rec.m_normal), 1.0);
		double sin_theta = std::sqrt(1.0 - cos_theta * cos_theta);

		bool cannot_refract = ri * sin_theta > 1.0;
		Vector3 direction;

		if (cannot_refract || reflectance(cos_theta, ri) > random_double())
			direction = reflect(unit_direction, rec.m_normal);
		else
			direction = refract(unit_direction, rec.m_normal, ri);

		scattered = Ray(rec.m_point, direction);
		return true;
	}

private:
	double _refractionIndex;


	static double reflectance(double cosine, double refraction_index) {
		auto r0 = (1 - refraction_index) / (1 + refraction_index);
		r0 = r0 * r0;
		return r0 + (1 - r0) * std::pow((1 - cosine), 5);
	}
};



#endif // !MATERIAL_H
