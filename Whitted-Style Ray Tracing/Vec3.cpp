#include "Vec3.h"

Vec3& Vec3::operator+=(const Vec3& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

Vec3& Vec3::operator*=(const float t)
{
	// TODO: 在此处插入 return 语句
	x *= t;
	y *= t;
	z *= t;
	return *this;
}

Vec3 Vec3::operator-() const
{
	return Vec3(-x,-y,-z);
}

float Vec3::length() const
{
	return sqrt(x * x + y * y + z * z);
}

Vec3 Vec3::random()
{
	return Vec3((rand() / (RAND_MAX + 1.0)), (rand() / (RAND_MAX + 1.0)), (rand() / (RAND_MAX + 1.0)));
}

Vec3 Vec3::random(float min, float max)
{
	return Vec3((min + (max - min) * (rand() / (RAND_MAX + 1.0))), (min + (max - min) * (rand() / (RAND_MAX + 1.0))), (min + (max - min) * (rand() / (RAND_MAX + 1.0))));
}

Vec3 Vec3::refract(const Vec3& uv, const Vec3& n, float eta)
{
	auto cos_theta = fmin(dot(-uv, n), 1.0);
	Vec3 r_out_perp = eta * (uv + cos_theta * n);
	Vec3 r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.length_squared())) * n;
	return r_out_parallel + r_out_perp;
}

Vec3 Vec3::reflect(Vec3 v, Vec3 n)
{
	return v - 2 * dot(v, n) * n;
}

bool Vec3::nearZero() const
{
	const auto s = 1e-8;
	return (x < s) && (y < s) && (z < s);
}

float Vec3::length_squared() const
{
	return x*x + y*y + z*z;
}
