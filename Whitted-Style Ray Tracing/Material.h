#pragma once
#include "Hittable.h"
const float pi = 3.141592653;
class Material
{
public:
	float random() const
	{
		return rand() / (RAND_MAX + 1.0);
	}

	float random(float min, float max) const
	{
		return min + (max - min) * random();
	}

	Vec3 randomDir() const
	{
		auto a = random(0, 2 * pi);
		auto z = random(-1, 1);
		auto r = sqrt(1 - z * z);
		return Vec3(r * cos(a), r * sin(a), z);
	}
	virtual bool scatter(const Ray& in,const hitRecord& recored,Color3& attenuation,Ray& out)const = 0;
};

