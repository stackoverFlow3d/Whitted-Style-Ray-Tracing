#include "Texture.h"

Color3 SolidColor::value(float u, float v, const Point3& p) const
{
    return colorValue;
}
