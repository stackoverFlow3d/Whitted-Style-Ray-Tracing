#pragma once
#include "Vec3.h"
#include <iostream>
class Ray
{
public:
	Point3 origin;
	Vec3 dir;
	float time;

	Ray() {};
	Ray(const Point3& origin0,const Vec3& dir0,float time0):origin(origin0),dir(dir0),time(time0) {};

	Point3 at(float t) const;
};

