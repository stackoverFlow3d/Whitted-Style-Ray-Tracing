#include <iostream>
#include "Vec3.h"
#include "Ray.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

bool hitBall(const Ray& r,const Point3& center,const float radius)
{
	float a, b, c,del;
	a = r.dir * r.dir;
	b = 2 * r.dir * (r.origin - center);
	c = (r.origin - center) * (r.origin - center) - radius * radius;
	del = b * b - 4 * a * c;
	if (del >= 0)
	{
		return true;
	}
	return false;
}

Color3 rayColor(const Ray& ray)
{
	//Ball
	Point3 center(0,0,-1);
	float radio = 0.5f;

	if (hitBall(ray,center,radio))
	{
		return Color3(0,0,1);
	}
	Vec3 unit = unit_vector(ray.dir);
	auto t = 0.5 * (unit.y + 1.0);
	//œﬂ–‘≤Â÷µ
	return (1.0 - t) * Color3(1.0, 1.0, 1.0) + t * Color3(0.5, 0.7, 1.0);
}

int main()
{
	//size of image
	const float scale = 16.0 / 9.0;
	const int width = 400;
	const int height = static_cast<int>(width / scale);

	//point of camera
	const float view_height = 2.0;
	const float view_width = view_height * scale;
	const float focal_length = 1.0;


	Vec3 horizontal(view_width, 0.0, 0.0);
	Vec3 vertical(0.0, view_height, 0.0);
	Point3 origin(0.0, 0.0, 0.0);
	Point3 lower_left_corner = origin - horizontal / 2 - vertical / 2 - Vec3(0, 0, focal_length);
	unsigned char* data = new unsigned char[width * height * 3];
	for (int j = height - 1; j >= 0; j--)
	{
		for (int i = 0; i < width; i++)
		{
			float u = float(i) / (width - 1);
			float v = float(height - 1 - j) / (height - 1);
			Ray r(origin, lower_left_corner + u * horizontal + v * vertical - origin);
			Color3 color = rayColor(r);
			data[j * width * 3 + i * 3 + 0] = int(255.99 * color.x);
			data[j * width * 3 + i * 3 + 1] = int(255.99 * color.y);
			data[j * width * 3 + i * 3 + 2] = int(255.99 * color.z);
		}
	}
	std::cout << "write png to file!" << std::endl;
	stbi_write_png("out1.png", width, height, 3, data, 0);
	stbi_image_free(data);
	return 0;
}