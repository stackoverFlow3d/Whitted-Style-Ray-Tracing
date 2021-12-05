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
