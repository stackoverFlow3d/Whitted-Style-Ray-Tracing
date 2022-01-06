#include "Diffuse.h"

Color3 Diffuse::emitted(float u, float v, const Point3& p) const
{
    return emit->value(u,v,p);
}

bool Diffuse::scatter(const Ray& in, const hitRecord& recored, Color3& attenuation, Ray& out) const
{
    return false;
}
