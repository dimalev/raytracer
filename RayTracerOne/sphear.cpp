#include "sphear.h"

sphere::sphere(const vec3 &center, float radius, material *mat) : C{ center }, R{ radius }, mat{ mat } { }

bool sphere::hits(const ray &r, float min_t, float max_t, hit_result &hitres) const {
	vec3 oc = r.origin() - C;
	float a = dot(r.direction(), r.direction());
	float b = dot(oc, r.direction());
	float c = dot(oc, oc) - R * R;
	float descriminant = b * b - a * c;
	if (descriminant > 0) {
		float temp = (-b - sqrtf(b * b - a * c)) / a;
		if (temp >= min_t && temp <= max_t) {
			hitres.t = temp;
			hitres.hit = r.point_at_parameter(temp);
			hitres.normal = (hitres.hit - C) / R;
			hitres.mat_ptr = mat;
			return true;
		}
		float temp2 = (-b + sqrtf(b * b - a * c)) / a;
		if (temp2 >= min_t && temp2 <= max_t) {
			hitres.t = temp2;
			hitres.hit = r.point_at_parameter(temp2);
			hitres.normal = (hitres.hit - C) / R;
			hitres.mat_ptr = mat;
			return true;
		}
		return false;
	}
	return false;
}
