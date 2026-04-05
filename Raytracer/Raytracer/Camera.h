#pragma once

#ifndef CAMERA_H
#define CAMERA_H

#include "Hittable.h"
#include "Colour.h"
#include "Material.h"

#ifdef _OPENMP
#include <omp.h>
#endif

#include <atomic>
#include <string>

#ifdef _WIN32
#include <windows.h>
#endif

class camera {
public:
	double aspect_ratio = 1.0;
	int    image_width = 100;
	int    samples_per_pixel = 10;
	int    max_depth = 10;

	double  verticalFOV = 90;
	point3  lookfrom = point3(0, 0, 0);
	point3  lookat = point3(0, 0, -1);
	Vector3 vup = Vector3(0, 1, 0);

	double defocus_angle = 0;
	double focus_dist = 10;

	void render(const hittable& world) {
		initialize();

		std::vector<std::string> row_buffers(image_height);
		for (auto& row : row_buffers)
			row.reserve(image_width * 12);

		std::atomic<int> rows_done{ 0 };

#pragma omp parallel
		{
#pragma omp single nowait
			{
				int reported = -1;
				while (true) {
					int done = rows_done.load(std::memory_order_relaxed);
					if (done != reported) {
						std::clog << "\rScanlines remaining: "
							<< (image_height - done) << "   " << std::flush;
						reported = done;
					}
					if (done >= image_height) break;
#ifdef _WIN32
					Sleep(0);
#else
					sched_yield();
#endif
				}
			}

#pragma omp for schedule(dynamic, 4)
			for (int j = 0; j < image_height; j++) {
				std::string& row = row_buffers[j];

				for (int i = 0; i < image_width; i++) {
					colour pixel_color(0, 0, 0);
					for (int sample = 0; sample < samples_per_pixel; sample++) {
						Ray r = get_ray(i, j);
						pixel_color += ray_colour(r, max_depth, world);
					}
					WriteColour(row, pixel_samples_scale * pixel_color);
				}

				rows_done.fetch_add(1, std::memory_order_relaxed);
			}
		}

		std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
		for (const auto& row : row_buffers)
			std::cout << row;

		std::clog << "\rDone.                 \n";
	}

private:
	int     image_height;
	double  pixel_samples_scale;
	point3  center;
	point3  pixel00_loc;
	Vector3 pixel_delta_u;
	Vector3 pixel_delta_v;
	Vector3 u, v, w;
	Vector3 defocus_disk_u;
	Vector3 defocus_disk_v;

	void initialize() {
		image_height = int(image_width / aspect_ratio);
		image_height = (image_height < 1) ? 1 : image_height;

		pixel_samples_scale = 1.0 / samples_per_pixel;

		center = lookfrom;

		double theta = deg2rad(verticalFOV);
		double h = std::tan(theta / 2);
		double viewport_height = 2 * h * focus_dist;
		double viewport_width = viewport_height * (double(image_width) / image_height);

		w = UnitVector(lookfrom - lookat);
		u = UnitVector(Cross(vup, w));
		v = Cross(w, u);

		Vector3 viewport_u = viewport_width * u;
		Vector3 viewport_v = viewport_height * -v;

		pixel_delta_u = viewport_u / image_width;
		pixel_delta_v = viewport_v / image_height;

		auto viewport_upper_left =
			center - (focus_dist * w) - viewport_u / 2 - viewport_v / 2;
		pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

		auto defocus_radius = focus_dist * std::tan(deg2rad(defocus_angle / 2));
		defocus_disk_u = u * defocus_radius;
		defocus_disk_v = v * defocus_radius;
	}

	Ray get_ray(int i, int j) const {
		auto offset = sample_square();
		auto pixel_sample = pixel00_loc
			+ ((i + offset.x()) * pixel_delta_u)
			+ ((j + offset.y()) * pixel_delta_v);

		auto ray_origin = (defocus_angle <= 0) ? center : defocus_disk_sample();
		auto ray_direction = pixel_sample - ray_origin;

		return Ray(ray_origin, ray_direction);
	}

	Vector3 sample_square() const {
		return Vector3(random_double() - 0.5, random_double() - 0.5, 0);
	}

	point3 defocus_disk_sample() const {
		auto p = random_in_unit_disk();
		return center + (p[0] * defocus_disk_u) + (p[1] * defocus_disk_v);
	}

	colour ray_colour(const Ray& r, int depth, const hittable& world) const {
		if (depth <= 0)
			return colour(0, 0, 0);

		hit_record rec;

		if (world.hit(r, interval(0.001, infinity), rec)) {
			Ray    scattered;
			colour attenuation;
			if (rec.m_material->scatter(r, rec, attenuation, scattered))
				return attenuation * ray_colour(scattered, depth - 1, world);
			return colour(0, 0, 0);
		}

		Vector3 unit_direction = UnitVector(r.direction());
		auto a = 0.5 * (unit_direction.y() + 1.0);
		return (1.0 - a) * colour(1.0, 1.0, 1.0) + a * colour(0.5, 0.7, 1.0);
	}
};

#endif // !CAMERA_H