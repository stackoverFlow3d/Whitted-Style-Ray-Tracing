#include "Dielectric.h"

Dielectric::Dielectric(float ir0)
{
	ir = ir0;
}

Vec3 Dielectric::refract(const Vec3& uv, const Vec3& n, float etai_over_etat) const
{
	auto cos_theta = fmin(dot(-uv, n), 1.0);
	Vec3 r_out_perp = etai_over_etat * (uv + cos_theta * n);
	Vec3 r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.length_squared())) * n;
	return r_out_parallel + r_out_perp;
}

bool Dielectric::scatter(const Ray& in, const hitRecord& recored, Color3& attenuation, Ray& out) const
{
	attenuation = Color3(1.0,1.0,1.0);
	float refraction_ratio = recored.isFront ? (1.0/ir) : ir;
	Vec3 unit_direction = unit_vector(in.dir);
	Vec3 refracted = refract(unit_direction,recored.normal, refraction_ratio);
	out = Ray(recored.hitPoint,refracted);
	return true;
}
