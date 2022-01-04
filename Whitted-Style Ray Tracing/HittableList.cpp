#include "HittableList.h"

HittableList::HittableList(shared_ptr<Hittable> object)
{
	objects.push_back(object);
}

void HittableList::clear()
{
	objects.clear();
}

bool HittableList::hit(const Ray& r, const float tmin, const float tmax, hitRecord& record) const
{
	bool isHit = false;
	hitRecord temp;
	float t = tmax;
	for (const auto& object:objects)
	{
		if (object->hit(r,tmin,t,temp))
		{
			isHit = true;
			t = temp.t;
			record = temp;
		}
	}
	return isHit;
}

bool HittableList::boundingBox(float time0, float time1, Aabb& outputBox) const
{
	if (objects.empty())
		return false;
	Aabb tempBox;
	bool isFirst = true;
	for (const auto& object : objects)
	{
		if (!object->boundingBox(time0, time1, tempBox))
			return false;
		outputBox = isFirst ? tempBox : surroundingBox(tempBox, outputBox);
		isFirst = false;
	}
	return true;
}
