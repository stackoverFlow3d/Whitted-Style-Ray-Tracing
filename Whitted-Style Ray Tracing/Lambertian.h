#pragma once
#include "Material.h"
class Lambertian :public Material
{
public:
	Color3 albedo;
	Lambertian() {};
	Lambertian(const Color3& a);
	virtual bool scatter(const Ray& in, const hitRecord& recored, Color3& attenuation, Ray& out) const override;
};

