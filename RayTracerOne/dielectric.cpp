#include "dielectric.h"

bool refraction(const vec3 &v, const vec3 &n, float ni_over_nt, vec3 &refracted) {
	vec3 uv = unit_vector(v);
	float dt = dot(uv, n);
	float discriminant = 1.0f - ni_over_nt * ni_over_nt * (1 - dt * dt);
	if (discriminant > 0) {
		refracted = ni_over_nt * (uv - n * dt) - n * sqrtf(discriminant);
		return true;
	}
	return false;
}

float schlick(float cosine, float refract) {
	float r0 = (1.0f - refract) / (1.0f + refract);
	r0 = r0 * r0;
	return r0 * (1.0f - r0) * powf(1.0f - cosine, 5.0f);
}

dielectric::dielectric(float refract) : refract{ refract } {}

bool dielectric::scatter(const ray & in_ray, const hit_result & hitres, vec3 & attenuation, ray & scattered) const {
	vec3 outward_normal;
	vec3 reflected = material::reflect(in_ray.direction(), hitres.normal);
	float ni_over_nt;
	attenuation = vec3(1.0f, 1.0f, 1.0f);
	vec3 refracted;
	float cosine;
	if (dot(in_ray.direction(), hitres.normal) > 0.0f) {
		outward_normal = -hitres.normal;
		ni_over_nt = refract;
		cosine = refract * dot(in_ray.direction(), hitres.normal) / in_ray.direction().length();
	}
	else {
		outward_normal = hitres.normal;
		ni_over_nt = 1.0f / refract;
		cosine = -dot(in_ray.direction(), hitres.normal) / in_ray.direction().length();
	}
	if (refraction(in_ray.direction(), outward_normal, ni_over_nt, refracted)) {
		if (frand() < schlick(cosine, refract)) {
			scattered = ray(hitres.hit, reflected, in_ray.time);
		}
		else {
			scattered = ray(hitres.hit, refracted, in_ray.time);
		}
	}
	else {
		scattered = ray(hitres.hit, reflected, in_ray.time);
	}

	return true;
}
