//
//  ScalingUtil.cpp
//  pxlframework
//
//  Created by Gaëtan de Villèle on 11/19/13.
//
//


#include "ScaleUtils.h"

// C++
#include <algorithm>
#include <cmath>
// px::tools
#include "utils.h"
#include "Device.h"


float px::engine::utils::scaling::pointToPixel()
{
    static float scale = -1.0f;
    
    // Lazy init
    if(scale < 0.0f)
    {
        tools::size screenSizeInPixels = tools::device::getScreenSizeInPixels(tools::device::ScreenOrientation::LANDSCAPE);
        
        float maxScale = 4.0f;
        
        // 375 x 210 points shall be visible
        float minPointsWidth = 450;
        float minPointsHeight = 280;
        
        float scaleOnWith = std::min(screenSizeInPixels.width / minPointsWidth, maxScale);
        float scaleOnHeight = std::min(screenSizeInPixels.height / minPointsHeight, maxScale);
        
        // maybe we should allow only 1,2,4,8... to keep a perfect pixel art aspect
        // a scale of 3 will not scale all pixels the same way
        
        scale = (std::min(scaleOnWith, scaleOnHeight));
        
        PXLLOG("Screen size in pixels: %.2f - %.2f", screenSizeInPixels.width,screenSizeInPixels.height);
        PXLLOG("Minimum points: %.2f - %.2f", minPointsWidth,minPointsHeight);
        PXLLOG("ScaleUtils::pointToPixel() : %.2f", scale);
    }
    
    return scale;
}



float px::engine::utils::scaling::pixelToPoint()
{
    static float scale = -1.0f;
    
    if (scale < 0.0)
    {
        scale = 1.0f / pointToPixel();
        PXLLOG("ScaleUtils::pixelToPoint() : %.2f", scale);
    }
	
    return scale;
}




