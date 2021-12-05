#include "Sphere.h"

bool Sphere::hit(const Ray& r, const float tmin, const float tmax, hitRecord& record) const
{
	float a, h, c, del;
	a = r.dir * r.dir;
	h = r.dir * (r.origin - center);
	c = (r.origin - center) * (r.origin - center) - radius * radius;
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
			return true;
		}
		t1 = (-h + sqrt(del)) / a;
		if (t1 > tmin && t1 < tmax)
		{
			record.t = t1;
			record.hitPoint = r.at(t1);
			record.normal = (record.hitPoint - center) / radius;
			return true;
		}
	}
	return false;
}
