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

Aabb surroundingBox(Aabb box0, Aabb box1);

