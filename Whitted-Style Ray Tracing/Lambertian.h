#pragma once
#include "Material.h"
#include "Texture.h"
class Lambertian :public Material
{
public:
	shared_ptr<Texture> albedo;
	Lambertian() {};
	Lambertian(const Color3& a) : albedo(make_shared<SolidColor>(a)) {};
	Lambertian(shared_ptr<Texture> a) : albedo(a) {};
	virtual bool scatter(const Ray& in, const hitRecord& recored, Color3& attenuation, Ray& out) const override;
};

