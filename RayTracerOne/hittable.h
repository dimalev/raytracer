#pragma once

#include "vec3.h"
#include "ray.h"

class material;

class hit_result {
public:
	vec3 hit, normal;
	float t;
	material *mat_ptr;
};

class hittable {
public:
	virtual bool hits(const ray &r, float min_t, float max_t, hit_result &hitres) const = 0;
};
