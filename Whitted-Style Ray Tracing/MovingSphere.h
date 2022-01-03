#pragma once
#include "Hittable.h"
class MovingSphere :
    public Hittable
{
public:
    float radius;
    shared_ptr<Material> mateptr;
    float time0, time1;
    Point3 center0, center1;
    MovingSphere() {};
    MovingSphere(Point3 _center0, Point3 _center1,float _time0,float _time1,float radius0, shared_ptr<Material> mateptr0) :center0(_center0), center1(_center1),time0(_time0),time1(_time1), radius(radius0), mateptr(mateptr0) {};
    Point3 center(float time) const;
    virtual bool hit(const Ray& r, const float tmin, const float tmax, hitRecord& record) const override;
    virtual bool boundingBox(float time0, float time1, Aabb& outputBox) const override;
};

