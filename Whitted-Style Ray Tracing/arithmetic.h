#pragma once
#include <iostream>
#include <cmath>
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;
inline float degrees_to_radians(double degrees)
{ //度数到弧度
	return degrees * pi / 180.0;
}
inline float randomFloat()
{
	return rand() / (RAND_MAX + 1.0);
}
inline float randomFloat(float t1, float t2)
{
	return t1 + (t2 - t1) * randomFloat();
}
inline float randomInt(int t1, int t2)
{
	return static_cast<int>(randomFloat(t1,t2+1));
}
inline double clamp(double x, double min, double max) 
{
	if (x < min) return min;
	if (x > max) return max;
	return x;
}