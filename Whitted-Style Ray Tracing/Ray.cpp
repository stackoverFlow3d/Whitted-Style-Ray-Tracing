#include "Ray.h"

Point3 Ray::at(float t) const
{
	return origin + t * dir;
}
