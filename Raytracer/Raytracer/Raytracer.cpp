#include "Raytracer.h"

double hit_sphere(const point3& center, double radius, const Ray& r) {
	Vector3 oc = center - r.origin();
	double a = Dot(r.direction(), r.direction());
	double b = -2.0 * Dot(r.direction(), oc);
	double c = Dot(oc, oc) - radius * radius;
	double discriminant = b * b - 4 * a * c;

	if (discriminant < 0)
		return -1.0;
	else
		return (-b - std::sqrt(discriminant)) / (2.0 * a);
}

colour ray_colour(const Ray& r) {
	double t = hit_sphere(point3(0, 0, -1), 0.5, r);
	if (t > 0.0) {
		Vector3 normal = UnitVector(r.at(t) - Vector3(0, 0, -1));
		return 0.5 * colour(normal.x() + 1, normal.y() + 1, normal.z() + 1);
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

			colour pixel_colour = ray_colour(r);

			WriteColour(std::cout, pixel_colour);
		}
	}

	std::clog << "\rDone.                     \n";
}