#include "simple_camera.h"
#include <opencv2/core/cvdef.h>

simple_camera::simple_camera() {}

simple_camera::simple_camera(const vec3 &lookfrom, const vec3 &lookat, const vec3 &vup, float vfov, float aspect) {
	vec3 u, v, w;
	float theta = vfov * CV_PI / 180.0f;
	float half_height = tan(theta / 2.0f);
	float half_width = aspect * half_height;
	this->origin = lookfrom;
	w = unit_vector(lookfrom - lookat);
	u = unit_vector(cross(vup, w));
	v = cross(w, u);
	this->lower_left = vec3(-half_width, -half_height, -1.0f);
	this->lower_left = this->origin - half_width * u - half_height * v - w;
	this->vertical = 2 * half_height * v;
	this->horizontal = 2 * half_width * u;
}

ray simple_camera::get_ray(float u, float v) {
	return ray(
		origin,
		lower_left + u * vertical + v * horizontal - origin
	);
}
