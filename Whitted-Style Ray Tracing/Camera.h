#pragma once
#include "Ray.h"

class Camera
{
public:
	Vec3 horizontal;
	Vec3 vertical;
	Point3 origin;
	Point3 lower_left_corner;
	Vec3 u, v, w;
	float lens_radius;
	Vec3 random_in_unit_disk() const;
	Camera(Point3 lookfrom,Point3 lookat,Vec3 up, float fov0,float aspect_ratio0,float aperture,float focusDis);
	Ray getRay(float u, float v) const;
};
inline float degrees_to_radians(double degrees) { //度数到弧度
	return degrees * 3.1415926535897932385 / 180.0;
}
inline float random()
{
	return rand() / (RAND_MAX + 1.0);
}
inline float random(float t1, float t2)
{
	return t1 + (t2 - t1) * random();
}

