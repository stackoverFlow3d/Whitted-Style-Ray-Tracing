#pragma once
#include <vector>
#include <memory>
#include "arithmetic.h"
#include "Aabb.h"
using namespace std;
class Material;
struct hitRecord
{
	Point3 hitPoint;
	Vec3 normal;
	float u, v;
	float t;
	bool isFront;
	shared_ptr<Material> mateptr;
	inline void setNormal(const Ray& r, const Vec3& out) 
	{
		isFront = (dot(r.dir , out)) < 0;
		normal = isFront ? out : -out;
	}
};
class Hittable
{
public:
	virtual bool hit(const Ray& r,const float tmin,const float tmax,hitRecord& record) const = 0;
	virtual bool boundingBox(float time0,float time1,Aabb& outputBox) const = 0;
};

class Translate : public Hittable
{
public:
    shared_ptr<Hittable> ptr;
    Vec3 offset;
    Translate(shared_ptr<Hittable> p, const Vec3& displacement)
        : ptr(p), offset(displacement) {}

    virtual bool hit(const Ray& r, const float tmin, const float tmax, hitRecord& record) const override;

    virtual bool boundingBox(float time0, float time1, Aabb& outputBox) const override;
   
};

class rotateY : public Hittable
{
public:
	shared_ptr<Hittable> ptr;
	float sin_theta;
	float cos_theta;
	bool hasbox;
	Aabb bbox;
	rotateY(shared_ptr<Hittable> p, float angle);

    virtual bool hit(const Ray& r, const float tmin, const float tmax, hitRecord& record) const override;

    virtual bool boundingBox(float time0, float time1, Aabb& outputBox) const override
	{
		outputBox = bbox;
        return hasbox;
    }
};
