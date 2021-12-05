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
