#pragma once
#include "Material.h"
class Meta :
    public Material
{
public:
    Color3 albedo;
    float fuzz;
    Vec3 reflect(Vec3 v,Vec3 n) const;
    Vec3 randomFuzz() const;
    Meta(Color3 albedo0,float fuzz0);
    virtual bool scatter(const Ray& in, const hitRecord& recored, Color3& attenuation, Ray& out)const override;
};
