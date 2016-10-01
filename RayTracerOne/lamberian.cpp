#include "lambertian.h"

lambertian::lambertian(const vec3 &a) :albedo{ a } {};

bool lambertian::scatter(const ray &in_ray, const hit_result &hitres, vec3 &attenuation, ray& scattered) const {
	vec3 target = hitres.hit + hitres.normal + vec3::random_unit_vector();
	scattered = ray(hitres.hit, target - hitres.hit);
	attenuation = albedo;
	return true;
}