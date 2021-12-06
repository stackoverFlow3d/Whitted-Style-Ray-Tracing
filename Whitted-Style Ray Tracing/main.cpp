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
#include "material.h"
#include "Lambertian.h"
#include "Meta.h"
#include "Dielectric.h"
const float infinity = std::numeric_limits<float>::infinity();
float random()
{
	return rand() / (RAND_MAX + 1.0);
}
Color3 rayColor(const Ray& r,const Hittable& scene,int depth)
{
	hitRecord record;
	if (depth < 0)
	{
		return Color3(0,0,0);
	}
	if (scene.hit(r,0.001,infinity,record))
	{
		Ray out;
		Color3 attenuation;
		if (record.mateptr->scatter(r, record, attenuation, out))
		{
			return attenuation * rayColor(out,scene,depth - 1);
		}
		return Color3(0,0,0);

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
	//depth
	const int max_depth = 50;
	//Camera
	Camera camera;
	//scene
	HittableList scene;
	auto material_ground = make_shared<Lambertian>(Color3(0.3, 0.8, 0.1));
	auto material_center = make_shared<Lambertian>(Color3(0.8, 0.1, 0.3));
	auto material_left = make_shared<Meta>(Color3(0.9, 0.1, 0),0.3);
	auto material_right = make_shared<Meta>(Color3(0.1, 0.2, 0.8),1);

	scene.add(make_shared<Sphere>(Point3(0.0, -100.5, -1.0), 100.0, material_ground));
	scene.add(make_shared<Sphere>(Point3(0.0, 0.0, -1.0), 0.5, material_center));
	scene.add(make_shared<Sphere>(Point3(-1.0, 0.0, -1.0), 0.5, material_left));
	scene.add(make_shared<Sphere>(Point3(1.0, 0.0, -1.0), 0.5, material_right));


	unsigned char* data = new unsigned char[width * height * 3];
	for (int j = height - 1; j >= 0; j--)
	{
		for (int i = 0; i < width; i++)
		{
			Color3 color(1,0,0);
			for (int s = 0; s < sample;s++) 
			{
				auto u = (i + random()) / width;
				auto v = (height - j + random() - 1) / height;
				Ray r = camera.getRay(u, v);
				color += rayColor(r, scene, max_depth);
			}
			auto r = sqrt(color.x / sample);
			auto g = sqrt(color.y / sample);
			auto b = sqrt(color.z / sample);
			data[j * width * 3 + i * 3 + 0] = int(255.99 * r);
			data[j * width * 3 + i * 3 + 1] = int(255.99 * g);
			data[j * width * 3 + i * 3 + 2] = int(255.99 * b);
		}
	}
	std::cout << "write png to file!" << std::endl;
	stbi_write_png("out1.png", width, height, 3, data, 0);
	stbi_image_free(data);
	return 0;
}