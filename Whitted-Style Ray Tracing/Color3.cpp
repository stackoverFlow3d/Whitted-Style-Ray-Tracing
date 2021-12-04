#include "Color3.h"

void writeColor3(std::ostream& out, Color3 pixel_color)
{
	//д��ÿ����ɫ����ת�����ֵ[0,255]
	out << static_cast<int>(255.999 * pixel_color.x) << ' '
		<< static_cast<int>(255.999 * pixel_color.y) << ' '
		<< static_cast<int>(255.999 * pixel_color.z) << '\n';
}