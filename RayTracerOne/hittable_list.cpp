#include "hittable_list.h"

hittable_list::hittable_list(hittable **list, int size) : list{ list }, size{ size } {}
hittable_list::hittable_list() : list{ nullptr }, size{ 0 } {}

bool hittable_list::hits(const ray &r, float min_t, float max_t, hit_result &hitres) const {
	hit_result temp_hit;
	float best_t = max_t;
	bool hit_anything = false;
	for (int i = 0; i < size; ++i) {
		if (list[i]->hits(r, min_t, best_t, temp_hit)) {
			hit_anything = true;
			best_t = temp_hit.t;
			hitres = temp_hit;
		}
	}
	return hit_anything;
}
