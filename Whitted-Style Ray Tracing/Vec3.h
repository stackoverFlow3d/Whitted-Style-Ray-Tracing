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
	float length() const;
};

using Point3 = Vec3;
using Color3 = Vec3;

inline Vec3 operator*(float t, const Vec3& v);
inline Vec3 operator+(const Vec3& u, const Vec3& v);