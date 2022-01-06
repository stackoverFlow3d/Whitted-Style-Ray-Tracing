#pragma once
#include "Hittable.h"

class XYrect : public Hittable
{
public:
	shared_ptr<Material> mp;
	float x0, x1, y0, y1, k;

	XYrect(){};
	XYrect(float _x0, float _x1, float _y0, float _y1, float _k,shared_ptr<Material> _mp):x0(_x0),x1(_x1),y0(_y0),y1(_y1),k(_k),mp(_mp) {};

	virtual bool hit(const Ray& r, const float tmin, const float tmax, hitRecord& record) const override;
	virtual bool boundingBox(float time0, float time1, Aabb& outputBox) const override;
};