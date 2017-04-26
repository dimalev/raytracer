#pragma once

#include "hittable.h"
#include "material.h"

class sphere : public hittable {
public:
	explicit sphere(const vec3 &center, float radius, material *mat);
	virtual bool hits(const ray &r, float min_t, float max_t, hit_result &hitres) const;

	mutable vec3 C;
	float R;
	material *mat;
};
