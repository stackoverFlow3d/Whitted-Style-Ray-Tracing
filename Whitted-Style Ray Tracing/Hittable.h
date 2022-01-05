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