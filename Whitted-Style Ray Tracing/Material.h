#pragma once
#include "Hittable.h"
class Material
{
public:
	virtual Color3 emitted(float u, float v, const Point3& p) const
	{
		return Color3(0, 0, 0);
	};
	virtual bool scatter(const Ray& in,const hitRecord& recored,Color3& attenuation,Ray& out)const = 0;
};

