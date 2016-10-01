#pragma once

#include "hittable.h"

class hittable_list : public hittable {
public:
	hittable_list();
	hittable_list(hittable **list, int size);
	virtual bool hits(const ray &r, float min_t, float max_t, hit_result &hitrse) const;

	hittable **list;
	int size;
};
