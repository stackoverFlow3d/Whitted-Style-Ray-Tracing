#include <iostream>
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
#include "arithmetic.h"
#include "MovingSphere.h"
#include "Bvh.h"
#include "CheckerTexture.h"
#include "Aarect.h"
#include "Diffuse.h"
#include "Box.h"

Color3 rayColor(const Ray& r,const Color3& background, const Hittable& scene,int depth)
{
	hitRecord record;
	if (depth < 0)
	{
		return Color3(0,0,0);
	}
	if (!scene.hit(r, 0.001, infinity, record))
	{
		return background;
	}
	Ray scattered;
	Color3 attenuation;
	Color3 emitted = record.mateptr->emitted(record.u, record.v, record.hitPoint);

	if (!record.mateptr->scatter(r, record, attenuation, scattered))
	{
		return emitted;
	}

	return emitted + attenuation * rayColor(scattered, background, scene, depth - 1);
}

HittableList randomScene() 
{
	HittableList scene;
	auto checker = make_shared<CheckerTexture>(Color3(0.2, 0.3, 0.1), Color3(0.9, 0.9, 0.9));
	scene.add(make_shared<Sphere>(Point3(0, -1000, 0), 1000, make_shared<Lambertian>(checker)));
	for (int a = -11; a < 11; a++) 
	{
		for (int b = -11; b < 11; b++) 
		{
			auto choose_mat = randomFloat();
			Point3 center(a + 0.9 * randomFloat(), 0.2, b + 0.9 * randomFloat());

			if ((center - Point3(4, 0.2, 0)).length() > 0.9) 
			{
				shared_ptr<Material> sphere_material;

				if (choose_mat < 0.8) 
				{
					// diffuse
					auto albedo = randomVec3() * randomVec3();
					sphere_material = make_shared<Lambertian>(albedo);
					Point3 center2 = center + Vec3(0, randomFloat(0,0.5), 0);
					scene.add(make_shared<MovingSphere>(center, center2,0.0,1.0,0.2, sphere_material));
				}
				else if (choose_mat < 0.95) 
				{
					// metal
					auto albedo = randomVec3(0.5, 1);
					auto fuzz = randomFloat(0, 0.5);
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
	return HittableList(make_shared<Bvh>(scene, 0, 1));
}

HittableList simpleLight()
{
	HittableList objects;
	auto pertext = make_shared<CheckerTexture>(Color3(0.2, 0.3, 0.1), Color3(0.9, 0.9, 0.9));
	objects.add(make_shared<Sphere>(Point3(0, -1000, 0), 1000, make_shared<Lambertian>(pertext)));
	objects.add(make_shared<Sphere>(Point3(0, 2, 0), 2, make_shared<Lambertian>(pertext)));

	auto difflight = make_shared<Diffuse>(Color3(4, 4, 4));
	objects.add(make_shared<XYrect>(3, 5, 1, 3, -2, difflight));

	return objects;
}
HittableList cornellBox() 
{
	HittableList objects;

	auto red = make_shared<Lambertian>(Color3(.65, .05, .05));
	auto white = make_shared<Lambertian>(Color3(.73, .73, .73));
	auto green = make_shared<Lambertian>(Color3(.12, .45, .15));
	auto light = make_shared<Diffuse>(Color3(15, 15, 15));

	objects.add(make_shared<YZrect>(0, 555, 0, 555, 555, green));
	objects.add(make_shared<YZrect>(0, 555, 0, 555, 0, red));
	objects.add(make_shared<XZrect>(213, 343, 227, 332, 554, light));
	objects.add(make_shared<XZrect>(0, 555, 0, 555, 0, white));
	objects.add(make_shared<XZrect>(0, 555, 0, 555, 555, white));
	objects.add(make_shared<XYrect>(0, 555, 0, 555, 555, white));
	
	shared_ptr<Hittable> box1 = make_shared<Box>(Point3(0, 0, 0), Point3(165, 330, 165), white);
	box1 = make_shared<rotateY>(box1, 15);
	box1 = make_shared<Translate>(box1, Vec3(265, 0, 295));
	objects.add(box1);

	shared_ptr<Hittable> box2 = make_shared<Box>(Point3(0, 0, 0), Point3(165, 165, 165), white);
	box2 = make_shared<rotateY>(box2, -18);
	box2 = make_shared<Translate>(box2, Vec3(130, 0, 65));
	objects.add(box2);
	return objects;
}
int main()
{
	//size of image
	const float scale = 1.0;
	const int width = 600;
	const int height = static_cast<int>(width / scale);
	Color3 background = Color3(0,0,0);
	//Sample
	const int sample = 1600;
	//depth
	const int maxDepth = 50;
	//Camera
	Point3 lookfrom(13, 2, 3);
	Point3 lookat(0, 0, 0);
	Vec3 vup(0, 1, 0);
	auto dist_to_focus = 10.0;
	auto aperture = 0.0;
	auto vfov = 40.0;
	//scene
	HittableList scene;

	scene = cornellBox();

	background = Color3(0, 0, 0);
	lookfrom = Point3(278, 278, -800);
	lookat = Point3(278, 278, 0);
	vfov = 40.0;

	Camera camera(lookfrom, lookat, vup, vfov, scale, aperture, dist_to_focus, 0.0, 1.0);
	unsigned char* data = new unsigned char[width * height * 3];
	for (int j = height - 1; j >= 0; j--)
	{
		std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
		for (int i = 0; i < width; i++)
		{
			Color3 color(1,0,0);
			for (int s = 0; s < sample;s++) 
			{
				auto u = (i + randomFloat()) / width;
				auto v = (height - j + randomFloat() - 1) / height;
				Ray r = camera.getRay(u, v);
				color += rayColor(r, background, scene, maxDepth);
			}
			auto r = sqrt(color.x / sample);
			auto g = sqrt(color.y / sample);
			auto b = sqrt(color.z / sample);
			data[j * width * 3 + i * 3 + 0] = int(256 * clamp(r, 0.0, 0.999));
			data[j * width * 3 + i * 3 + 1] = int(256 * clamp(g, 0.0, 0.999));
			data[j * width * 3 + i * 3 + 2] = int(256 * clamp(b, 0.0, 0.999));
		}
	}
	std::cout << "render done!" << std::endl;
	stbi_write_png("out1.png", width, height, 3, data, 0);
	stbi_image_free(data);
	return 0;
}