#pragma once

#include "material.h"

class dielectric : public material {
public:
	dielectric(float refract);
	bool scatter(const ray & in_ray, const hit_result & hitres, vec3 & attenuation, ray & scattered) const;

	float refract;
};