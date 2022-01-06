#include "Aarect.h"

bool XYrect::hit(const Ray& r, const float tmin, const float tmax, hitRecord& record) const
{
    auto t = (k - r.origin.z) / r.dir.z;
    if (t < tmin || t > tmax)
        return false;
    auto x = r.origin.x + t * r.dir.x;
    auto y = r.origin.y + t * r.dir.y;
    if (x < x0 || x > x1 || y < y0 || y > y1)
        return false;
    record.u = (x - x0) / (x1 - x0);
    record.v = (y - y0) / (y1 - y0);
    record.t = t;
    auto outward_normal = Vec3(0, 0, 1);
    record.setNormal(r, outward_normal);
    record.mateptr = mp;
    record.hitPoint = r.at(t);
    return true;
}

bool XYrect::boundingBox(float time0, float time1, Aabb& outputBox) const
{
	outputBox = Aabb(Point3(x0, y0, k - 0.0001), Point3(x1, y1, k + 0.0001));
	return true;
}
