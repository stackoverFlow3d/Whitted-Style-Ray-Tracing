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

float Vec3::length() const
{
	return sqrt(x * x + y * y + z * z);
}

inline Vec3 operator*(float t, const Vec3& v)
{
	return Vec3(t * v.x, t * v.y, t * v.z);
}

inline Vec3 operator+(const Vec3& u, const Vec3& v)
{
	return Vec3(u.x + v.x,u.y + v.y,u.z + v.z);
}
