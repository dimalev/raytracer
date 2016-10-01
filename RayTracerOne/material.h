#pragma once

#include "ray.h"
#include "hittable.h"

class material {
public:
	virtual bool scatter(const ray &in_ray, const hit_result &hitres, vec3 &attenuation, ray &scattered) const = 0;

	static vec3 reflect(const vec3 &v, const vec3 &n);
};