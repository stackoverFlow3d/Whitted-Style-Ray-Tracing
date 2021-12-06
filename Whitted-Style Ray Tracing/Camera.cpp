#include "Camera.h"
Camera::Camera(Point3 lookfrom, Point3 lookat, Vec3 up, float fov0, float aspect_ratio0, float aperture, float focusDis)
{
    auto theta = degrees_to_radians(fov0);
    auto h = tan(theta / 2);
    auto viewport_height = 2.0 * h;
    auto viewport_width = aspect_ratio0 * viewport_height;
    w = unit_vector(lookfrom - lookat);
    u = unit_vector(cross(up, w));
    v = cross(w, u);

    origin = lookfrom;
    horizontal = focusDis * viewport_width * u;
    vertical = focusDis * viewport_height * v;
    lower_left_corner = origin - horizontal / 2 - vertical / 2 - focusDis * w;

    lens_radius = aperture / 2;
}
Vec3 Camera::random_in_unit_disk() const
{
    while (true) 
    {
        auto p = Vec3(random(-1, 1), random(-1, 1), 0);
        if (p.length_squared() >= 1) continue;
        return p;
    }
}
Ray Camera::getRay(float s,float t) const
{
    Vec3 rd = lens_radius * random_in_unit_disk();
    Vec3 offset = rd.x * u + rd.y * v;

    return Ray(
        origin + offset,
        lower_left_corner + s * horizontal + t * vertical - origin - offset);
}

