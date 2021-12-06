#include "Lambertian.h"

Lambertian::Lambertian(const Color3& a)
{
	albedo = a;
}

bool Lambertian::scatter(const Ray& in, const hitRecord& recored, Color3& attenuation, Ray& out) const
{
	Vec3 outdir = recored.normal + randomDir();
	if (outdir.nearZero())
	{
		outdir = randomDir();
	}
	out = Ray(recored.hitPoint, outdir);
	attenuation = albedo;
	return true;
}

