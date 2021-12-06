#pragma once
#include "Hittable.h"
class Sphere :
    public Hittable
{
public:
    Point3 center;
    float radius;
    shared_ptr<Material> mateptr;

    Sphere() {};
    Sphere(Point3 center0, float radius0, shared_ptr<Material> mateptr0) :center(center0), radius(radius0),mateptr(mateptr0) {};
    virtual bool hit(const Ray& r, const float tmin, const float tmax, hitRecord& record) const override;
};

