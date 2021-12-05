#pragma once
#include "Ray.h"

class Camera
{
public:
	Vec3 horizontal;
	Vec3 vertical;
	Point3 origin;
	Point3 lower_left_corner;
	Camera();
	Ray getRay(float u, float v);
};

