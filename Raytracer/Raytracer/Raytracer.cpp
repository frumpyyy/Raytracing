#include "Raytracer.h"

colour ray_colour(const Ray& r, const hittable& world) {
	hit_record record;
	if (world.hit(r, 0, infinity, record)) {
		return 0.5 * (record.m_normal + colour(1, 1, 1));
	}


	Vector3 unitDirection = UnitVector(r.direction());
	auto a = 0.5 * (unitDirection.y() + 1.0);
	return (1.0 - a) * colour(1.0, 1.0, 1.0) + a * colour(0.5, 0.7, 1.0);
}


int main() {
	//image parameter creation

	double aspect_ratio = 16.0 / 9.0;
	int image_width = 400;

	//calculate image height based on aspect ratio and image width
	int image_height = int(image_width / aspect_ratio);

	//lambda to ensure that image height is always at least 1 pixel
	image_height = (image_height < 1) ? 1 : image_height;

	//world

	hittable_list world;

	world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
	world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));


	//camera

	double focal_length = 1.0;
	double viewport_height = 2.0;
	double viewport_width = viewport_height * (double(image_width) / image_height);
	Vector3 camera_center = point3(0, 0, 0);

	Vector3 viewport_u = Vector3(viewport_width, 0, 0);
	Vector3 viewport_v = Vector3(0, -viewport_height, 0);

	Vector3 pixel_delta_u = viewport_u / image_width;
	Vector3 pixel_delta_v = viewport_v / image_height;

	Vector3 viewport_top_left = camera_center - Vector3(0, 0, focal_length) -
		viewport_u / 2 - viewport_v / 2;

	Vector3 pixel00_location = viewport_top_left + 0.5 * (pixel_delta_u + pixel_delta_v);

	//image rendering
	std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	for (int j = 0; j < image_height; j++) {
		std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
		for (int i = 0; i < image_width; i++) {
			Vector3 pixel_center = pixel00_location + (i * pixel_delta_u) + (j * pixel_delta_v);
			Vector3 rayDirection = pixel_center - camera_center;

			Ray r(camera_center, rayDirection);

			colour pixel_colour = ray_colour(r, world);

			WriteColour(std::cout, pixel_colour);
		}
	}

	std::clog << "\rDone.                     \n";
}