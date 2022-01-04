#pragma once
#include "Hittable.h"
#include "HittableList.h"
#include <algorithm>
class Bvh :public Hittable
{
public:
	shared_ptr<Hittable> left;
	shared_ptr<Hittable> right;
	Aabb box;

	Bvh() {};
	Bvh(const std::vector<shared_ptr<Hittable>>& srcObjects,int start,int end,float time0,float time1);
	Bvh(const HittableList& list, float time0, float time1) :Bvh(list.objects, 0, list.objects.size(), time0, time1) {};
	virtual bool hit(const Ray& r, const float tmin, const float tmax, hitRecord& record) const override;
	virtual bool boundingBox(float time0, float time1, Aabb& outputBox) const override;
};

inline bool compareBox(const shared_ptr<Hittable> a, shared_ptr<Hittable> b,int axis)
{
	Aabb boxA,boxB;
	if (!a->boundingBox(0, 0, boxA) || !b->boundingBox(0, 0, boxB))
	{
		std::cerr << "No bounding box in Bvh";
	}
	return boxA.min[axis] < boxB.min[axis];
}

bool compareBoxX(const shared_ptr<Hittable> a, shared_ptr<Hittable> b);
bool compareBoxY(const shared_ptr<Hittable> a, shared_ptr<Hittable> b);
bool compareBoxZ(const shared_ptr<Hittable> a, shared_ptr<Hittable> b);
