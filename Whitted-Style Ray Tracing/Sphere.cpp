#include "Sphere.h"

bool Sphere::hit(const Ray& r, const float tmin, const float tmax, hitRecord& record) const
{
	float a, h, c, del;
	a = dot(r.dir , r.dir);
	h = dot(r.dir , (r.origin - center));
	c = dot((r.origin - center) , (r.origin - center)) - radius * radius;
	del = h * h - a * c;
	if (del > 0)
	{
		float t1 = (-h - sqrt(del)) / a;
		if (t1 > tmin && t1 < tmax)
		{
			record.t = t1;
			record.hitPoint = r.at(t1);
			Vec3 normal1 = (record.hitPoint - center) / radius;
			record.setNormal(r, normal1);
			record.mateptr = mateptr;
			return true;
		}
		t1 = (-h + sqrt(del)) / a;
		if (t1 > tmin && t1 < tmax)
		{
			record.t = t1;
			record.hitPoint = r.at(t1);
			Vec3 normal2 = (record.hitPoint - center) / radius;
			record.setNormal(r, normal2);
			record.mateptr = mateptr;
			return true;
		}
	}
	return false;
}

bool Sphere::boundingBox(float time0, float time1, Aabb& outputBox) const
{
	outputBox = Aabb((center - Vec3(radius, radius, radius)), (center + Vec3(radius, radius, radius)));
	return true;
}
