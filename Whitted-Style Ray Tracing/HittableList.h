#pragma once
#include "Hittable.h"
#include <vector>
#include <memory>
using namespace std;
class HittableList :
    public Hittable
{
public:
    vector<shared_ptr<Hittable>> objects;
    HittableList() {};
    HittableList(shared_ptr<Hittable> object);
    void clear();
    void add(shared_ptr<Hittable> object) { objects.push_back(object); }
    virtual bool hit(const Ray& r, const float tmin, const float tmax, hitRecord& record) const override;
};

