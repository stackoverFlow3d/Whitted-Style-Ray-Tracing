#pragma once
#include <iostream>
#include <cmath>

class Vec3
{
public:
	float x, y, z;
	Vec3():x(0),y(0),z(0) {};
	Vec3(const float x0, const float y0, const float z0):x(x0),y(y0),z(z0) {};
	Vec3& operator+=(const Vec3& v);
	Vec3& operator*=(const float t);
	Vec3 operator-() const;
	float length() const;
	static Vec3 random();
	static Vec3 random(float min,float max);
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
inline Vec3 operator/(const Vec3& v, double t) 
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
inline Vec3 cross(const Vec3& u, const Vec3& v) {
	return Vec3(u.y * v.z - u.z * v.y,
		u.z * v.x - u.x * v.z,
		u.x * v.y - u.y * v.x);
}