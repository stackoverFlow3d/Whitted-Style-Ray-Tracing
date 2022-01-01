#include "MovingSphere.h"

Point3 MovingSphere::center(float time) const
{
    return center0 + ((time - time0)/(time1 - time0)) * (center1 - center0);
}

bool MovingSphere::hit(const Ray& r, const float tmin, const float tmax, hitRecord& record) const
{
	float a, h, c, del;
	a = dot(r.dir, r.dir);
	h = dot(r.dir, (r.origin - center(r.time)));
	c = dot((r.origin - center(r.time)), (r.origin - center(r.time))) - radius * radius;
	del = h * h - a * c;
	if (del > 0)
	{
		float t1 = (-h - sqrt(del)) / a;
		if (t1 > tmin && t1 < tmax)
		{
			record.t = t1;
			record.hitPoint = r.at(t1);
			Vec3 normal1 = (record.hitPoint - center(r.time)) / radius;
			record.setNormal(r, normal1);
			record.mateptr = mateptr;
			return true;
		}
		t1 = (-h + sqrt(del)) / a;
		if (t1 > tmin && t1 < tmax)
		{
			record.t = t1;
			record.hitPoint = r.at(t1);
			Vec3 normal2 = (record.hitPoint - center(r.time)) / radius;
			record.setNormal(r, normal2);
			record.mateptr = mateptr;
			return true;
		}
	}
	return false;
}
