//
//  ColorUtils.h
//  pxlframework
//
//  Created by Adrien Duermaël on 24/10/11.
//
//


#ifndef __pxlframework__ColorUtils__
#define __pxlframework__ColorUtils__


// C++
#include <stdlib.h>
#include <stdio.h>
#include <utility>
#include <string>
#include <sstream>


typedef struct HSVColor {
	signed int h;
	unsigned char s;
	unsigned char v;
} HSVColor;



typedef struct RGBAColor
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t a;
} RGBAColor;



inline RGBAColor RGBAColorMake(std::string rgbHex, uint8_t a)
{
	//	int num = std::stoi(rgbHex, 0, 16);
	unsigned int num;
	std::stringstream ss;
	ss << std::hex << rgbHex;
	ss >> num;
	
	RGBAColor color;
	
	color.r = num / 0x10000;
	color.g = (num / 0x100) % 0x100;
	color.b = num % 0x100;
	color.a = a;
	
	return color;
}



inline RGBAColor RGBAColorMake(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	RGBAColor color;
	color.r = r;
	color.g = g;
	color.b = b;
	color.a = a;
	
	return color;
}



inline RGBAColor RGBAColorZero()
{
	RGBAColor color;
	color.r = 0;
	color.g = 0;
	color.b = 0;
	color.a = 0;
	
	return color;
}



inline bool RGBAColorEqual(RGBAColor a, RGBAColor b)
{
	return (a.r == b.r && a.g == b.g && a.b == b.b && a.a == b.a);
}



inline bool HSVColorEqual(HSVColor a, HSVColor b)
{
	return (a.h == b.h && a.s == b.s && a.v == b.v);
}


namespace px
{
	namespace engine
	{
		namespace utils
		{
			namespace color
			{
				HSVColor RGBA2HSV(const RGBAColor& RGB);
				RGBAColor HSV2RGBA(const HSVColor& HSV);
				RGBAColor rgbaRandomFromHSV(float h, float s, float v);
				RGBAColor rgbaRandomFromHSV(const HSVColor& HSV);
			}
		}
	}
}


#endif




