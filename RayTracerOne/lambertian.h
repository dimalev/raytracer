#pragma once

#include "material.h"

class lambertian : public material {
public:
	lambertian(const vec3 &a);

	vec3 albedo;
	bool scatter(const ray & in_ray, const hit_result & hitres, vec3 & attenuation, ray & scattered) const;
};