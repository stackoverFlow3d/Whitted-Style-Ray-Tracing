#pragma once
#include "Hittable.h"
#include "HittableList.h"
#include "Aarect.h"
class Box :
    public Hittable
{
public:
    Point3 boxMin;
    Point3 boxMax;
    HittableList sides;
    Box() {};
    Box(const Point3& p0, const Point3& p1, shared_ptr<Material> ptr);
    virtual bool hit(const Ray& r, const float tmin, const float tmax, hitRecord& record) const override;
    virtual bool boundingBox(float time0, float time1, Aabb& outputBox) const override;
};

