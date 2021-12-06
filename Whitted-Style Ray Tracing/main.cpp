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

HittableList randomScene() 
{
	HittableList scene;
	auto ground_material = make_shared<Lambertian>(Color3(0.3, 0.8, 0.1));
	scene.add(make_shared<Sphere>(Point3(0, -1000, 0), 1000, ground_material));
	for (int a = -11; a < 11; a++) 
	{
		for (int b = -11; b < 11; b++) 
		{
			auto choose_mat = random();
			Point3 center(a + 0.9 * random(), 0.2, b + 0.9 * random());

			if ((center - Point3(4, 0.2, 0)).length() > 0.9) 
			{
				shared_ptr<Material> sphere_material;

				if (choose_mat < 0.8) 
				{
					// diffuse
					auto albedo = Color3::random() * Color3::random();
					sphere_material = make_shared<Lambertian>(albedo);
					scene.add(make_shared<Sphere>(center, 0.2, sphere_material));
				}
				else if (choose_mat < 0.95) 
				{
					// metal
					auto albedo = Color3::random(0.5, 1);
					auto fuzz = random(0, 0.5);
					sphere_material = make_shared<Meta>(albedo, fuzz);
					scene.add(make_shared<Sphere>(center, 0.2, sphere_material));
				}
				else {
					// glass
					sphere_material = make_shared<Dielectric>(1.5);
					scene.add(make_shared<Sphere>(center, 0.2, sphere_material));
				}
			}
		}
	}
	auto material1 = make_shared<Dielectric>(1.5);
	scene.add(make_shared<Sphere>(Point3(0, 1, 0), 1.0, material1));
	auto material2 = make_shared<Lambertian>(Color3(0.4, 0.2, 0.1));
	scene.add(make_shared<Sphere>(Point3(-4, 1, 0), 1.0, material2));
	auto material3 = make_shared<Meta>(Color3(0.7, 0.6, 0.5), 0.0);
	scene.add(make_shared<Sphere>(Point3(4, 1, 0), 1.0, material3));
	return scene;
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
	Point3 lookfrom(3, 3, 2);
	Point3 lookat(0, 0, -1);
	Vec3 vup(0, 1, 0);
	auto dist_to_focus = (lookfrom - lookat).length();
	auto aperture = 2.0;

	Camera camera(lookfrom, lookat, vup, 20, scale, aperture, dist_to_focus);
	//scene
	HittableList scene;
	auto material_ground = make_shared<Lambertian>(Color3(0.3, 0.8, 0.1));
	auto material_center = make_shared<Lambertian>(Color3(0.8, 0.1, 0.3));
	auto material_left = make_shared<Dielectric>(1.5);
	auto material_right = make_shared<Meta>(Color3(0.8, 0.6, 0.2), 0.0);

	scene.add(make_shared<Sphere>(Point3(0.0, -100.5, -1.0), 100.0, material_ground));
	scene.add(make_shared<Sphere>(Point3(0.0, 0.0, -1.0), 0.5, material_center));
	scene.add(make_shared<Sphere>(Point3(-1.0, 0.0, -1.0), 0.5, material_left));
	scene.add(make_shared<Sphere>(Point3(-1.0, 0.0, -1.0), -0.45, material_left));
	scene.add(make_shared<Sphere>(Point3(1.0, 0.0, -1.0), 0.5, material_right));


	unsigned char* data = new unsigned char[width * height * 3];
	for (int j = height - 1; j >= 0; j--)
	{
		std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
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