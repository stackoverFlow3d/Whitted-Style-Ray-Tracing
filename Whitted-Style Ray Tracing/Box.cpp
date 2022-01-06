#include "Box.h"

Box::Box(const Point3& p0, const Point3& p1, shared_ptr<Material> ptr)
{
    boxMin = p0;
    boxMax = p1;

    sides.add(make_shared<XYrect>(p0.x, p1.x, p0.y, p1.y, p1.z, ptr));
    sides.add(make_shared<XYrect>(p0.x, p1.x, p0.y, p1.y, p0.z, ptr));

    sides.add(make_shared<XZrect>(p0.x, p1.x, p0.z, p1.z, p1.y, ptr));
    sides.add(make_shared<XZrect>(p0.x, p1.x, p0.z, p1.z, p0.y, ptr));

    sides.add(make_shared<YZrect>(p0.y, p1.y, p0.z, p1.z, p1.x, ptr));
    sides.add(make_shared<YZrect>(p0.y, p1.y, p0.z, p1.z, p0.x, ptr));
}

bool Box::hit(const Ray& r, const float tmin, const float tmax, hitRecord& record) const
{
    return sides.hit(r, tmin, tmax, record);
}

bool Box::boundingBox(float time0, float time1, Aabb& outputBox) const
{
    outputBox = Aabb(boxMin,boxMax);
    return true;
}
