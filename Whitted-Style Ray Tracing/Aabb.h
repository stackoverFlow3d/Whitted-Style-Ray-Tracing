#pragma once
#include "arithmetic.h"
#include "Vec3.h"
#include "Ray.h"
class Aabb
{
public:
	Point3 min;
	Point3 max;
	Aabb() {};
	Aabb(const Point3& min0, const Point3& max0):min(min0),max(max0) {};
	bool hit(const Ray& ray, float t0, float t1) const;
};
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

