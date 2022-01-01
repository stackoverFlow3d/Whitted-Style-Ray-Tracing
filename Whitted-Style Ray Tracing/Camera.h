#pragma once
#include "Ray.h"
#include "arithmetic.h"
class Camera
{
public:
	Vec3 horizontal;
	Vec3 vertical;
	Point3 origin;
	Point3 lower_left_corner;
	Vec3 u, v, w;
	float lens_radius;
	float time0, time1;
	Vec3 random_in_unit_disk() const;
	Camera(Point3 lookfrom,Point3 lookat,Vec3 up, float fov0,float scale,float aperture,float focusDis,float _time0,float _time1);
	Ray getRay(float u, float v) const;
};


