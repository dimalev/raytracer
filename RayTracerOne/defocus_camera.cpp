#include "defocus_camera.h"
#include <opencv2/core/cvdef.h>

vec3 random_in_unit_disk() {
	vec3 p;
	do {
		p = 2.0f * vec3(frand(), frand(), 0.0f) - vec3(1.0f, 1.0f, 0.0f);
	} while (dot(p, p) >= 1.0f);
	return p;
}

defocus_camera::defocus_camera() {}

defocus_camera::defocus_camera(const vec3 &lookfrom, const vec3 &lookat, const vec3 &vup, float vfov, float aspect, float aperture, float focus_dist) {
	lens_radius = aperture / 2.0f;
	float theta = vfov * CV_PI / 180.0f;
	float half_height = tan(theta / 2.0f);
	float half_width = aspect * half_height;
	origin = lookfrom;
	w = unit_vector(lookfrom - lookat);
	u = unit_vector(cross(vup, w));
	v = cross(w, u);
	lower_left = origin - half_width * focus_dist * u - half_height * focus_dist * v - focus_dist * w;
	vertical = 2 * half_height * focus_dist * v;
	horizontal = 2 * half_width * focus_dist * u;
}

ray defocus_camera::get_ray(float s, float t) {
	vec3 rd = lens_radius * random_in_unit_disk();
	vec3 offset = u * rd.x() + v * rd.y();
	return ray(
		origin + offset,
		lower_left + s * vertical + t * horizontal - origin - offset
	);
}
