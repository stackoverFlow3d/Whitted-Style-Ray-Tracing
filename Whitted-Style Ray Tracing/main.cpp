#include <iostream>
#include "Vec3.h"
#include "Ray.h"
#include "Color3.h"
//size of image
const float scale = 16 / 9;
const int width = 400;
const int height = static_cast<int>(width / scale);

//point of camera
const float view_height = 2;
const float view_width = view_height * scale;
const float focal_length = 1;
int main()
{
	std::cout << "P3\n" << width << ' ' << height << "\n255\n";
	for (int j = height - 1; j >= 0; --j)
	{
		for (int i = 0; i < width; ++i)
		{
			double r = double(i) / (width - 1);
			double g = double(j) / (height - 1);
			double b = 0.25;
			Color3 pixel_color(r, g, b);
			writeColor3(std::cout, pixel_color);
		}
	}
	return 0;
}