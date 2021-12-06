#pragma once
#include "Ray.h"
#include <vector>
#include <memory>
using namespace std;
class Material;
struct hitRecord
{
	Point3 hitPoint;
	Vec3 normal;
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
};

