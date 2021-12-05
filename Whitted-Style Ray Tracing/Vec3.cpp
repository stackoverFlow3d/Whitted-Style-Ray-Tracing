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
	// TODO: �ڴ˴����� return ���
	x *= t;
	y *= t;
	z *= t;
	return *this;
}

float Vec3::length() const
{
	return sqrt(x * x + y * y + z * z);
}
