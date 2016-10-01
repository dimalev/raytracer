#include "metal.h"


metal::metal(const vec3 &a, float fuzz) : albedo{ a }, fuzz{ fuzz } {};
bool metal::scatter(const ray &in_ray, const hit_result &hitres, vec3 &attenuation, ray &scattered) const {
	vec3 reflected = material::reflect(unit_vector(in_ray.direction()), hitres.normal);
	scattered = ray(hitres.hit, reflected + fuzz * vec3::random_unit_vector());
	attenuation = albedo;
	return dot(scattered.direction(), hitres.normal) > 0;
}
