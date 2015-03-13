//
//  Label.cpp
//  pxlframework
//
//  Created by Gaëtan de Villèle on 10/30/13.
//
//


#include "Label.h"


namespace px
{
	namespace engine
	{
		
#pragma mark - Construction functions -
		
		Label* Label::newLabel(const MenuSprite::RelativePosition relativePosition,
							   const MenuSprite::RelativePosition anchor,
							   const Point& position,
							   const std::string& text,
							   const std::string& font)
		{
			Label* result = new Label();
			
			// define MenuSprite specific attributes
			result->setRelativePosition(relativePosition);
			result->setAnchor(MenuSprite::convertRelativePositionIntoAnchorPoint(anchor));
			result->setPosition( Point(position.getX2D(), position.getY2D()) );
			
			// define Label specific attributes
			result->setText(text);
			result->setFont(font);
			
			return result;
		}
        
        
        Label* Label::newLabel(const MenuSprite::RelativePosition relativePosition,
                               const MenuSprite::RelativePosition anchor,
                               const Point& position,
                               const std::string& text,
                               const std::string& font,
                               const float fontSize)
        {
            Label* result = Label::newLabel(relativePosition,anchor, position, text, font);
            result->setFontSize(fontSize);
            return result;
            
        }
        
        
        
		
		
		Label* Label::newLabel(const Point& anchor,
							   const Point& position,
							   const std::string& text,
							   const std::string& font)
		{
			Label* result = new Label();
			
			// define MenuSprite specific attributes
			result->setAnchor(anchor);
			result->setPosition(position);
			
			// define Label specific attributes
			result->setText(text);
			result->setFont(font);
			
			return result;
		}
        
        
        Label* Label::newLabel(const Point& anchor,
                               const Point& position,
                               const std::string& text,
                               const std::string& font,
                               const float fontSize)
        {
            Label* result = Label::newLabel(anchor, position, text, font);
            result->setFontSize(fontSize);
            return result;
        }
        
        
		
		
#pragma mark - Constructor / Destructor -
		
		Label::Label() : MenuSprite(),
		_text(),
		_sizeToReserve(0),
		_maxWidth(0),
        _fontSize(10),
        _bitmap(false)
		{
			setType(Sprite::Type::LABEL);
		}
		
		
		
		/*virtual*/
		Label::~Label()
		{}
		
		
		
#pragma mark - Methods -
		
		
		
		
#pragma mark - Accessors -
		
		
		
		
#pragma mark - Modifiers -
		
		
		
	}
}




