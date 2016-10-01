#pragma once

#include "camera.h"

class defocus_camera : public camera {
public:
	defocus_camera();
	defocus_camera(const vec3 &lookfrom, const vec3 &lookat, const vec3 &vup, float vfov, float aspect, float aperture, float focus_dist);
	virtual ray get_ray(float u, float v);

	vec3 origin, lower_left, vertical, horizontal;
	vec3 u, v, w;
	float lens_radius;
};
