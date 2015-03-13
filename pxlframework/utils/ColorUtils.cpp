//
//  ColorUtils.m
//  pxlframework
//
//  Created by Adrien Duermaël on 24/10/11.
//
//


#include "ColorUtils.h"

// C++
#include <map>
#include <cmath>


using namespace std;


HSVColor px::engine::utils::color::RGBA2HSV(const RGBAColor& RGB)
{
    unsigned char min, max, delta;
    HSVColor HSV;
    
    if (RGB.r < RGB.g) min = RGB.r; else min = RGB.g;
    if (RGB.b < min) min = RGB.b;
    
    if (RGB.r > RGB.g) max = RGB.r; else max = RGB.g;
    if (RGB.b > max) max = RGB.b;
    
    HSV.v = max;
    
    delta = max - min;
    
    if (max == 0)
    {
        HSV.s = 0;
        HSV.h = 0;
    }
    else
    {
        HSV.s = (int)((delta<<8) - delta) / max;
    
#if TARGET_IPHONE_SIMULATOR
        if( delta == 0 ) delta = 1;
#endif

        if (RGB.r == max)
            HSV.h = (RGB.g - RGB.b) * 60 / delta;        // between yellow & magenta
        else if( RGB.g == max )
            HSV.h = 120 + (RGB.b - RGB.r) * 60 / delta;    // between cyan & yellow
        else
            HSV.h = 240 + (RGB.r - RGB.g) * 60 / delta;    // between magenta & cyan

        if (HSV.h < 0)
            HSV.h += 360;
    }

    return HSV;
}



RGBAColor px::engine::utils::color::HSV2RGBA(const HSVColor& HSV)
{
    int i;
    float f, p, q, t, h, s, v;
    RGBAColor RGB;
    
    h = (float)HSV.h;
    s = (float)HSV.s;
    v = (float)HSV.v;
    
    s /= 255;
    
    if (s == 0)
    {
        RGB.r = RGB.g = RGB.b = v;
    }
    else
    {
        h /= 60;
        i = h > 0 ? (int)h : (int)h - 1;    // avoid the use of floor
        f = h - i;
        p = (unsigned char)(v * (1 - s));
        q = (unsigned char)(v * (1 - s * f));
        t = (unsigned char)(v * (1 - s * (1 - f)));
        
        switch (i)
        {
            case 0:
                RGB.r = v;
                RGB.g = t;
                RGB.b = p;
                break;
            case 1:
                RGB.r = q;
                RGB.g = v;
                RGB.b = p;
                break;
            case 2:
                RGB.r = p;
                RGB.g = v;
                RGB.b = t;
                break;
            case 3:
                RGB.r = p;
                RGB.g = q;
                RGB.b = v;
                break;
            case 4:
                RGB.r = t;
                RGB.g = p;
                RGB.b = v;
                break;
            default:
                RGB.r = v;
                RGB.g = p;
                RGB.b = q;
                break;
        }
    }
        
    return RGB;
}



RGBAColor px::engine::utils::color::rgbaRandomFromHSV(float h, float s, float v)
{
    const float goldenRatioConjugate = 0.618033988749895;
    h += goldenRatioConjugate;
    h = fmod(h, 1);
    
    float r = 0;
    float g = 0;
    float b = 0;
    
    int hInt = (h * 6);
    float fraction = (h * 6) - hInt;
    
    float p = v * (1 - s);
    float q = v * (1 - fraction * s);
    float t = v * (1 - (1 - fraction) * s);
    
    switch (hInt)
    {
        case 0:
            r = v;
            g = t;
            b = p;
            break;
        case 1:
            r = q;
            g = v;
            b = p;
            break;
        case 2:
            r = p;
            g = v;
            b = t;
            break;
        case 3:
            r = p;
            g = q;
            b = v;
            break;
        case 4:
            r = t;
            g = p;
            b = v;
            break;
        case 5:
            r = v;
            g = p;
            b = q;
            break;
    }
    
    RGBAColor color;
    color.r = (uint8_t)(r * 255);
    color.g = (uint8_t)(g * 255);
    color.b = (uint8_t)(b * 255);
    color.a = 255;
    
    return color;
}



RGBAColor px::engine::utils::color::rgbaRandomFromHSV(const HSVColor& HSV)
{
    return rgbaRandomFromHSV(HSV.h,HSV.s,HSV.v);
}




