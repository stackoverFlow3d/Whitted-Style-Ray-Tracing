#include "Dielectric.h"

Dielectric::Dielectric(float ir0)
{
	ir = ir0;
}

float Dielectric::relectance(float cosine, float ref_idx)
{
	// Use Schlick's approximation for reflectance.
	auto r0 = (1 - ref_idx) / (1 + ref_idx);
	r0 = r0 * r0;
	return r0 + (1 - r0) * pow((1 - cosine), 5);
}

bool Dielectric::scatter(const Ray& in, const hitRecord& recored, Color3& attenuation, Ray& out) const
{
	attenuation = Color3(1.0,1.0,1.0);
	float refraction_ratio = recored.isFront ? (1.0/ir) : ir;
	Vec3 unit_direction = unit_vector(in.dir);
	double cos_theta = fmin(dot(-unit_direction, recored.normal), 1.0);
	double sin_theta = sqrt(1.0 - cos_theta * cos_theta);

	bool cannot_refract = refraction_ratio * sin_theta > 1.0;
	Vec3 direction;

	if (cannot_refract || relectance(cos_theta, refraction_ratio) > randomFloat())
		direction = Vec3::reflect(unit_direction, recored.normal);
	else
		direction = Vec3::refract(unit_direction, recored.normal, refraction_ratio);

	out = Ray(recored.hitPoint, direction, in.time);
	return true;
}

