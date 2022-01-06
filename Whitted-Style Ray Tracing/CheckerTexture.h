#pragma once
#include "Texture.h"
#include <memory>
using namespace std;
class CheckerTexture :
    public Texture
{
public:
    shared_ptr<Texture> odd;
    shared_ptr<Texture> even;

    CheckerTexture() {};
    CheckerTexture(shared_ptr<Texture> odd0, shared_ptr<Texture> even0):odd(odd0),even(even0) {};
    CheckerTexture(Color3 c1,Color3 c2) :odd(make_shared<SolidColor>(c1)), even(make_shared<SolidColor>(c2)) {};
    virtual Color3 value(float u, float v, const Point3& p)const override;
};

