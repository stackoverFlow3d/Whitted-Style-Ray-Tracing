#pragma once
#include "Hittable.h"
class Sphere :
    public Hittable
{
public:
    Point3 center;
    float radius;
    Sphere() {};
    Sphere(Point3 center0, float radius0) :center(center0), radius(radius0) {};
    virtual bool hit(const Ray& r, const float tmin, const float tmax, hitRecord& record) const override;
};

