#include "moving_sphere.h"

moving_sphere::moving_sphere(float radius, material *mat,
                             const vec3 &center0, const vec3 &center1,
                             float time0, float time1)
: sphere{center0, radius, mat}, center0{center0}, center1{center1},
  time0{time0}, time1{time1} {}

vec3 moving_sphere::center(float time) const {
  return center0 + (time - time0) / (time1 - time0) * (center1 - center0);
}

bool moving_sphere::hits(const ray &r, float min_t, float max_t, hit_result &hitres) const {
  C = center(r.time);
  return sphere::hits(r, min_t, max_t, hitres);
}
