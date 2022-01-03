#include "Meta.h"

Vec3 Meta::randomFuzz() const
{
    while (true) 
    {
        Vec3 p = randomVec3(-1, 1);
        if ( p.length() * p.length() >= 1)
            continue;
        return p;
    }
}

Meta::Meta(Color3 albedo0,float fuzz0)
{
    fuzz = fuzz0;
    albedo = albedo0;
}

bool Meta::scatter(const Ray& in, const hitRecord& recored, Color3& attenuation, Ray& out) const
{
    Vec3 outDir = Vec3::reflect(unit_vector(in.dir),recored.normal);
    out = Ray(recored.hitPoint,outDir + fuzz* randomFuzz(), in.time);
    attenuation = albedo;
    return (dot(out.dir , recored.normal) > 0);
}
