#pragma once
#include "Hittable.h"
#include "HittableList.h"
class Bvh :public Hittable
{
public:
	shared_ptr<Hittable> left;
	shared_ptr<Hittable> right;
	Aabb box;

	Bvh() {};
	Bvh(const std::vector<Hittable>& srcObjects,int start,int end,float time0,float time1);
	Bvh(const HittableList& list, float time0, float time1) { Bvh(list.objects, 0, list.objects.size(), time0, time1); };
	virtual bool hit(const Ray& r, const float tmin, const float tmax, hitRecord& record) const;
	virtual bool boundingBox(float time0, float time1, Aabb& outputBox) const;
};

