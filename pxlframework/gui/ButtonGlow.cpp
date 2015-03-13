//
//  ButtonGlow.cpp
//  pxlframework
//
//  Created by Axel Guilmin on 7/10/14.
//
//


#include "ButtonGlow.h"

// pxlframework
#include "actions.h"


namespace px
{
	namespace engine
	{
        
        /*static*/ ButtonGlow* ButtonGlow::newButtonGlow(const std::string& textureName,
                                                         const std::string& glowTextureName,
                                                         const MenuSprite::RelativePosition relativePosition,
                                                         const MenuSprite::RelativePosition anchor,
                                                         const Point& position,
                                                         FunctionPointerHandler* target,
                                                         px::FunctionPointerButtonCallback selector)
        {
            ButtonGlow *result = new ButtonGlow();
            
			// define MenuSprite specific attributes
			result->setTextureName(textureName);
			result->setRelativePosition(relativePosition);
			result->setAnchor(MenuSprite::convertRelativePositionIntoAnchorPoint(anchor));
			result->setPosition(Point(position.getX2D(), position.getY2D()));
			
			// define Button specific stuff
			result->setTarget(target);
			result->setSelector(selector);
            
            // Add the glow
            result->_glow = MenuSprite::newMenuSpriteWithTexture(glowTextureName, MenuSprite::RelativePosition::CENTER, MenuSprite::RelativePosition::CENTER, {0.0f, 0.0f});
            result->addChild(result->_glow);
            
            
            result->_glow->setOpacity(0.0f);
            result->_glow->runAction(ActionRepeatForever::withAction(ActionSequence::withActions(SpriteActionFadeTo::withDuration(0.5f, 0.0f),
                                                                                                 SpriteActionFadeTo::withDuration(0.5f, 1.0f))));
            
            result->setImportant(true);
            
            return result;
        }
    }
}




