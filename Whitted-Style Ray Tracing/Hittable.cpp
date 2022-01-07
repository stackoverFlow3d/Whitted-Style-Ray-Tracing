#include "Hittable.h"
bool Translate::hit(const Ray& r, const float tmin, const float tmax, hitRecord& record) const
{
    Ray moved_r(r.origin - offset, r.dir, r.time);
    if (!ptr->hit(moved_r, tmin, tmax, record))
        return false;

    record.hitPoint += offset;
    record.setNormal(moved_r, record.normal);

    return true;
}

bool Translate::boundingBox(float time0, float time1, Aabb& outputBox) const
{
    if (!ptr->boundingBox(time0, time1, outputBox))
        return false;

    outputBox = Aabb(
        outputBox.min + offset,
        outputBox.max + offset);

    return true;
}
rotateY::rotateY(shared_ptr<Hittable> p, float angle) : ptr(p)
{
    auto radians = degrees_to_radians(angle);
    sin_theta = sin(radians);
    cos_theta = cos(radians);
    hasbox = ptr->boundingBox(0, 1, bbox);

    Point3 min(infinity, infinity, infinity);
    Point3 max(-infinity, -infinity, -infinity);

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            for (int k = 0; k < 2; k++)
            {
                auto x = i * bbox.max.x + (1 - i) * bbox.min.x;
                auto y = j * bbox.max.y + (1 - j) * bbox.min.y;
                auto z = k * bbox.max.z + (1 - k) * bbox.min.z;

                auto newx = cos_theta * x + sin_theta * z;
                auto newz = -sin_theta * x + cos_theta * z;

                Vec3 tester(newx, y, newz);

                for (int c = 0; c < 3; c++) 
                {
                    min[c] = fmin(min[c], tester[c]);
                    max[c] = fmax(max[c], tester[c]);
                }
            }
        }
    }

    bbox = Aabb(min, max);
}

bool rotateY::hit(const Ray& r, const float tmin, const float tmax, hitRecord& record) const
{
    auto origin = r.origin;
    auto direction = r.dir;

    origin[0] = cos_theta * r.origin[0] - sin_theta * r.origin[2];
    origin[2] = sin_theta * r.origin[0] + cos_theta * r.origin[2];

    direction[0] = cos_theta * r.dir[0] - sin_theta * r.dir[2];
    direction[2] = sin_theta * r.dir[0] + cos_theta * r.dir[2];

    Ray rotated_r(origin, direction, r.time);

    if (!ptr->hit(rotated_r, tmin, tmax, record))
        return false;

    auto p = record.hitPoint;
    auto normal = record.normal;

    p[0] = cos_theta * record.hitPoint[0] + sin_theta * record.hitPoint[2];
    p[2] = -sin_theta * record.hitPoint[0] + cos_theta * record.hitPoint[2];

    normal[0] = cos_theta * record.normal[0] + sin_theta * record.normal[2];
    normal[2] = -sin_theta * record.normal[0] + cos_theta * record.normal[2];

    record.hitPoint = p;
    record.setNormal(rotated_r, normal);

    return true;
}