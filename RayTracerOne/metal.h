#pragma once

#include "material.h"
#include "hittable.h"

class metal : public material {
public:
	metal(const vec3 &a, float fuzz);
	bool scatter(const ray &in_ray, const hit_result &hitres, vec3 &attenuation, ray &scattered) const;

	vec3 albedo;
	float fuzz;
};