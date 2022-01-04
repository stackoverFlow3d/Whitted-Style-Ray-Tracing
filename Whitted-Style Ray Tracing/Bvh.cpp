#include "Bvh.h"

Bvh::Bvh(const std::vector<shared_ptr<Hittable>>& srcObjects, int start, int end, float time0, float time1)
{
	auto objects = srcObjects;
	int axis = randomInt(0, 2);
	auto comparaor = compareBoxX;
	switch (axis)
	{
	default:
		break;
	case(0):comparaor = compareBoxX; break;
	case(1):comparaor = compareBoxY; break;
	case(2):comparaor = compareBoxZ; break;
	}
	int length = end - start;
	if (length == 1)
	{
		left = right = objects[start];
	}
	else if(length == 2)
	{
		 if(comparaor(objects[start], objects[start+1]))
		 {
			 left = objects[start];
			 right = objects[start + 1];
		 }
		 else
		 {
			 left = objects[start+1];
             right = objects[start];
		 }
	}
	else
	{
		std::sort(objects.begin() + start, objects.begin() + end,comparaor);
		auto mid = start + length/2;
		left = make_shared<Bvh>(objects,start,mid,time0,time1);
		right = make_shared<Bvh>(objects, mid, end, time0, time1);
	}

	Aabb boxLeft, boxRight;
	if (!left->boundingBox(time0,time1,boxLeft) || !right->boundingBox(time0, time1, boxRight))
	{
		std::cerr << "No bounding box in Bvh";
	}
	box = surroundingBox(boxLeft,boxRight);
}

bool Bvh::hit(const Ray& r, const float tmin, const float tmax, hitRecord& record) const
{
	if(!box.hit(r,tmin,tmax))
		return false;
	bool hitLeft = left->hit(r, tmin, tmax, record);
	bool hitRight = right->hit(r, tmin, tmax, record);
	return hitLeft || hitRight;
}

bool Bvh::boundingBox(float time0, float time1, Aabb& outputBox) const
{
	outputBox = box;
	return true;
}

bool compareBoxX(const shared_ptr<Hittable> a, shared_ptr<Hittable> b)
{
	return compareBox(a, b, 0);
}

bool compareBoxY(const shared_ptr<Hittable> a, shared_ptr<Hittable> b)
{
	return compareBox(a, b, 1);
}

bool compareBoxZ(const shared_ptr<Hittable> a, shared_ptr<Hittable> b)
{
	return compareBox(a, b, 2);
}
