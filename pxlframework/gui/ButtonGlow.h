//
//  ButtonGlow.h
//  pxlframework
//
//  Created by Axel Guilmin on 7/10/14.
//
//


#ifndef __pxlframework__ButtonGlow__
#define __pxlframework__ButtonGlow__


// pxlframework
#include "Button.h"


namespace px
{
	namespace engine
	{
        class ButtonGlow : public Button
        {
			
        public:
            
            /**
             * no reference position
             * it will be positionned relative to screen if it has no parent
             * and relative to its parent if it has one
             */
            static ButtonGlow* newButtonGlow(const std::string& textureName,
                                             const std::string& glowTextureName,
                                             const MenuSprite::RelativePosition relativePosition,
                                             const MenuSprite::RelativePosition anchor,
                                             const Point& position,
                                             FunctionPointerHandler* target,
                                             px::FunctionPointerButtonCallback selector);
            
            /**
             * Destructor
             */
            virtual ~ButtonGlow() {};
			
			
        protected:
			
			
        private:
            
            MenuSprite *_glow = nullptr;
        };
    }
}


#endif




