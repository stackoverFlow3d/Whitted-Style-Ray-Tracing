#pragma once
#include "Vec3.h"
class Texture
{
public:
	virtual Color3 value(float u,float v,const Point3& p)const = 0;
};

class SolidColor : public Texture
{
public:
	Color3 colorValue;
	SolidColor() {};
	SolidColor(Color3 color):colorValue(color) {};
	SolidColor(float red, float green, float blue) :colorValue(Color3(red,green,blue)) {};

	virtual Color3 value(float u, float v, const Point3& p)const override;
};