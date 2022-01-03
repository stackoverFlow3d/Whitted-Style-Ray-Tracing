#include "Aabb.h"

bool Aabb::hit(const Ray& ray, float t0, float t1) const
{
	for (int a = 0; a < 3; a++)
	{
        auto invD = 1.0f / ray.dir[a];
        auto t0p = (min[a] - ray.origin[a]) * invD;
        auto t1p = (max[a] - ray.origin[a]) * invD;
        if (invD < 0.0f)
            std::swap(t0, t1);
        t0 = t0p > t0 ? t0p : t0;
        t1 = t1p < t1 ? t1p : t1;
        if (t1 <= t0)
            return false;
	}
    return true;
}
