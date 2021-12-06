#pragma once
#include "Material.h"
class Dielectric :
    public Material
{
private:
    static float relectance(float cosine, float ref_idx);
public:
    float ir;
    Dielectric(float ir0);
    virtual bool scatter(const Ray& in, const hitRecord& recored, Color3& attenuation, Ray& out)const override;
};

