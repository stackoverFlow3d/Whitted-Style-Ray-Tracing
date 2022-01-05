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
    virtual bool boundingBox(float time0, float time1, Aabb& outputBox) const override;
private:
    static void getUV(const Point3& p,float& u,float& v);
};

