#pragma once

#include "sphere.h"
#include "material.h"

class moving_sphere : public sphere {
public:
	explicit moving_sphere(float radius, material *mat,
                         const vec3 &center0, const vec3 &center1,
                         float time0, float time1);

	virtual bool hits(const ray &r, float min_t, float max_t, hit_result &hitres) const;
  vec3 center(float time) const;

  vec3 center0, center1;
  float time0, time1;
};
