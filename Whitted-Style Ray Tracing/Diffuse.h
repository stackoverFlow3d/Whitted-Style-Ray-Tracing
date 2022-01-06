#pragma once
#include "Material.h"
#include "Texture.h"
class Diffuse :
    public Material
{
public:
	shared_ptr<Texture> emit;
	Diffuse() {};
	Diffuse(shared_ptr<Texture> emit0) :emit(emit0) {};
	Diffuse(Color3 c) :emit(make_shared<SolidColor>(c)) {};
	virtual Color3 emitted(float u, float v, const Point3& p) const override;
	virtual bool scatter(const Ray& in, const hitRecord& recored, Color3& attenuation, Ray& out)const override;
};

