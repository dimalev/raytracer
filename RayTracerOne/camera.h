#pragma once

#include "vec3.h"
#include "ray.h"

class camera {
public:
	virtual ray get_ray(float u, float v) = 0;
};