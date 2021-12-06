#pragma once
#include "Material.h"
class Dielectric :
    public Material
{
public:
    float ir;
    Dielectric(float ir0);
    Vec3 refract(const Vec3& uv,const Vec3& n,float eta) const;
    virtual bool scatter(const Ray& in, const hitRecord& recored, Color3& attenuation, Ray& out)const override;
};

