#include <iostream>
#include "Vec3.h"
#include "Ray.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "HittableList.h"
#include "Sphere.h"
#include "Camera.h"

const double infinity = std::numeric_limits<double>::infinity();

float random()
{
	return rand() / (RAND_MAX + 1.0);
}

Color3 rayColor(const Ray& r,const Hittable& scene)
{
	hitRecord record;
	if (scene.hit(r,0,infinity,record))
	{
		return 0.5 * Vec3(record.normal.x + 1, record.normal.y + 1, record.normal.z + 1);
	}
	Vec3 unit = unit_vector(r.dir);
	float t = 0.5 * (unit.y + 1.0);
	//œﬂ–‘≤Â÷µ
	return (1.0 - t) * Color3(1.0, 1.0, 1.0) + t * Color3(0.5, 0.7, 1.0);
}

int main()
{
	//size of image
	const float scale = 16.0 / 9.0;
	const int width = 400;
	const int height = static_cast<int>(width / scale);
	//Sample
	const int sample = 100;
	//Camera
	Camera camera;
	//scene
	HittableList scene;
	Sphere s1(Point3(0,0,-1),0.5f);
	Sphere ground(Point3(0, -100.5, -1), 100);
	scene.add(make_shared<Sphere>(s1));
	scene.add(make_shared<Sphere>(ground));

	unsigned char* data = new unsigned char[width * height * 3];
	for (int j = height - 1; j >= 0; j--)
	{
		for (int i = 0; i < width; i++)
		{
			Color3 color(0,0,0);
			for (int s = 0; s < sample;s++) 
			{
				auto u = (i + random()) / width;
				auto v = (height - j + random() - 1) / height;
				Ray r = camera.getRay(u, v);
				color += rayColor(r, scene);
			}
			data[j * width * 3 + i * 3 + 0] = int(255.99 * color.x) / sample;
			data[j * width * 3 + i * 3 + 1] = int(255.99 * color.y) / sample;
			data[j * width * 3 + i * 3 + 2] = int(255.99 * color.z) / sample;
		}
	}
	std::cout << "write png to file!" << std::endl;
	stbi_write_png("out1.png", width, height, 3, data, 0);
	stbi_image_free(data);
	return 0;
}