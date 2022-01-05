#include "Lambertian.h"

bool Lambertian::scatter(const Ray& in, const hitRecord& recored, Color3& attenuation, Ray& out) const
{
	Vec3 outdir = recored.normal + randomDir();
	if (outdir.nearZero())
	{
		outdir = randomDir();
	}
	out = Ray(recored.hitPoint, outdir,in.time);
	attenuation = albedo->value(recored.u, recored.v, recored.hitPoint);
	return true;
}

