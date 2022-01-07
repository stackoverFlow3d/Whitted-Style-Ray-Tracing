#pragma once
#include <iostream>
#include <cmath>
#include "arithmetic.h"
class Vec3
{
public:
	float x, y, z;
	Vec3():x(0),y(0),z(0) {};
	Vec3(const float x0, const float y0, const float z0):x(x0),y(y0),z(z0) {};
	Vec3& operator+=(const Vec3& v);
	Vec3& operator*=(const float t);
	Vec3 operator-() const;
	float operator[](int i) const
	{
		if (i == 0)
			return x;
		else if (i == 1)
			return y;
		else if (i == 2)
			return z;
	};
	float& operator[](int i)
	{
		if (i == 0)
			return x;
		else if (i == 1)
			return y;
		else if (i == 2)
			return z;
	};
	float length() const;
	static Vec3 refract(const Vec3& uv, const Vec3& n, float eta);
	static Vec3 reflect(Vec3 v, Vec3 n);
	bool nearZero() const;
	float length_squared() const;
};

using Point3 = Vec3;
using Color3 = Vec3;

inline Vec3 operator*(float t, const Vec3& v)
{
	return Vec3(t * v.x, t * v.y, t * v.z);
}
inline Vec3 operator*(const Vec3& v1, const Vec3& v2)
{
	return Vec3(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
}
inline Vec3 operator+(const Vec3& u, const Vec3& v)
{
	return Vec3(u.x + v.x, u.y + v.y, u.z + v.z);
}
inline Vec3 operator-(const Vec3& u, const Vec3& v)
{
	return Vec3(u.x - v.x, u.y - v.y, u.z - v.z);
}
inline Vec3 operator/(const Vec3& v, float t) 
{
	return (1 / t) * v;
}
inline Vec3 unit_vector(const Vec3& v) 
{
	return v / v.length();
}
inline float dot(const Vec3& v1, const Vec3& v2)
{
	return v1.x * v2.x + v2.y * v1.y + v1.z * v2.z;
}
inline Vec3 cross(const Vec3& u, const Vec3& v) 
{
	return Vec3(u.y * v.z - u.z * v.y,
		u.z * v.x - u.x * v.z,
		u.x * v.y - u.y * v.x);
}
inline Vec3 random_in_unit_disk() 
{
	while (true) 
	{
		auto p = Vec3(randomFloat(-1, 1), randomFloat(-1, 1), 0);
		if (p.length_squared() >= 1) continue;
		return p;
	}
}
inline Vec3 randomDir()
{
	auto a = randomFloat(0, 2 * pi);
	auto z = randomFloat(-1, 1);
	auto r = sqrt(1 - z * z);
	return Vec3(r * cos(a), r * sin(a), z);
}
inline static Vec3 randomVec3()
{
	return Vec3(randomFloat(), randomFloat(), randomFloat());
}
inline static Vec3 randomVec3(float min, float max)
{
	return Vec3(randomFloat(min,max), randomFloat(min, max), randomFloat(min, max));
}
