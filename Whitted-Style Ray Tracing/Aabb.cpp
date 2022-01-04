#include "Aabb.h"

bool Aabb::hit(const Ray& ray, float t0, float t1) const
{
    for (int a = 0; a < 3; a++) 
    {
        auto fmin1 = fmin((min[a] - ray.origin[a]) / ray.dir[a],
            (max[a] - ray.origin[a]) / ray.dir[a]);
        auto fmax1 = fmax((min[a] - ray.origin[a]) / ray.dir[a],
            (max[a] - ray.origin[a]) / ray.dir[a]);
        t0 = fmax(t0, fmin1);
        t1 = fmin(t1, fmax1);
        if (t1 <= t0)
            return false;
    }
    return true;
}

Aabb surroundingBox(Aabb box0, Aabb box1)
{
	Point3 small(fmin(box0.min.x, box1.min.x),
		fmin(box0.min.y, box1.min.y),
		fmin(box0.min.z, box1.min.z));

	Point3 big(fmax(box0.max.x, box1.max.x),
		fmax(box0.max.y, box1.max.y),
		fmax(box0.max.z, box1.max.z));

	return Aabb(small, big);
}
