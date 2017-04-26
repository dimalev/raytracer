#pragma once

#include "camera.h"

class simple_camera : public camera {
public:
	simple_camera();
	simple_camera(const vec3 &lookfrom, const vec3 &lookat, const vec3 &vup,
    float vfov, float aspect, float time0, float time1);
	virtual ray get_ray(float u, float v);
	vec3 origin, lower_left, vertical, horizontal;
  float time0, time1;
};
