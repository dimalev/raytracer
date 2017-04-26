#pragma once

#include "vec3.h"

class ray {
public:
	ray() {}
	ray(const vec3 &origin, const vec3 &direction, const float& time) :
		A{origin}, B{direction}, time{time} {}
	vec3 origin() const { return A; }
	vec3 direction() const { return B; }
	vec3 point_at_parameter(float t) const { return A + t * B; }

	vec3 A, B;
	float time;
};
