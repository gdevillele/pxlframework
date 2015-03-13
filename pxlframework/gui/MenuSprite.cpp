//
//  MenuElement.cpp
//  pxlframework
//
//  Created by Gaëtan de Villèle on 8/26/13.
//
//


#include "MenuSprite.h"

// pxlframework
#include "ScaleUtils.h"
#include "Button.h"


namespace px
{
	namespace engine
	{
#pragma mark - static methods -
		
		Point MenuSprite::convertRelativePositionIntoAnchorPoint(RelativePosition relativePosition)
		{
			Point result(0.0f, 0.0f);
			switch (relativePosition)
			{
				case RelativePosition::CENTER:
					result.set2D(0.5f, 0.5f);
					break;
				case RelativePosition::TOP:
					result.set2D(0.5f, 1.0f);
					break;
				case RelativePosition::TOP_RIGHT:
					result.set2D(1.0f, 1.0f);
					break;
				case RelativePosition::RIGHT:
					result.set2D(1.0f, 0.5f);
					break;
				case RelativePosition::BOTTOM_RIGHT:
					result.set2D(1.0f, 0.0f);
					break;
				case RelativePosition::BOTTOM:
					result.set2D(0.5f, 0.0f);
					break;
				case RelativePosition::BOTTOM_LEFT:
					// keep [0.0f, 0.0f]
					break;
				case RelativePosition::LEFT:
					result.set2D(0.0f, 0.5f);
					break;
				case RelativePosition::TOP_LEFT:
					result.set2D(0.0f, 1.0f);
					break;
				default:
					PXLLOG("[MenuSprite::convertRelativePositionIntoAnchorPoint] position is UNDEFINED");
					break;
			}
			return result;
		}
		
		
		
#pragma mark - factory methods -
		
		MenuSprite* MenuSprite::newMenuSprite(const Size contentSize,
											  const MenuSprite::RelativePosition relativePosition,
											  const MenuSprite::RelativePosition anchor,
                                              const Point& position)
		{
			MenuSprite* result = new MenuSprite();
			
			if( ! result->init(contentSize, relativePosition, anchor, position) )
			{
				delete result;
				result = nullptr;
			}
			
			return result;
		}
		
		
		
		bool MenuSprite::init(const Size contentSize,
							  const MenuSprite::RelativePosition relativePosition,
							  const MenuSprite::RelativePosition anchor,
							  const Point& position)
		{
			setType(Sprite::Type::NOTEXTURE);
			setContentSize(contentSize);
			setRelativePosition(relativePosition);
			setAnchor(MenuSprite::convertRelativePositionIntoAnchorPoint(anchor));
			setPosition( Point(position.getX2D(), position.getY2D()) );
			
			return true;
		}
		
		
		
		MenuSprite* MenuSprite::newMenuSpriteWithTexture(const std::string& textureName,
														 const MenuSprite::RelativePosition relativePosition,
														 const MenuSprite::RelativePosition anchor,
														 const Point& position)
		{
			MenuSprite* result = new MenuSprite();
			result->setTextureName(textureName);
			result->setRelativePosition(relativePosition);
			result->setAnchor(MenuSprite::convertRelativePositionIntoAnchorPoint(anchor));
			result->setPosition( Point(position.getX2D(), position.getY2D()) );
			return result;
		}
		
		
		
		MenuSprite* MenuSprite::newMenuSprite(const std::string& textureName)
		{
			MenuSprite* result = new MenuSprite();
			result->setTextureName(textureName);
			return result;
		}
		
		
		
#pragma mark - Constructor / Destructor -
		
		MenuSprite::MenuSprite() : Sprite(),
		_state(State::NORMAL),
		_relativePosition(RelativePosition::UNDEFINED),
		_parallaxFactor(1.0f),
        _scaledToFitDeviceResolution(false),
		_anchorToBeForcedTo(RelativePosition::UNDEFINED)
		{}
		
		
		
		/*virtual*/
		MenuSprite::~MenuSprite()
		{}
		
		
		
#pragma mark - Methods -
		
		bool MenuSprite::onTouch( TouchEvent event )
		{
			if(_state == State::DISABLED)
				return false;
			
			// a pure MenuSprite object does not respond to touch events
			// but it can has children which actually respond to touch
			// so it dispatch the event to its children
			
			// we modify the touch even : we convert the touch coordinates
			// into this menu sprite coordinates
			// (the ZERO is the bottom left corner of this menusprite)
			
			TouchEvent localevent = convertTouchEventCoordinates(event);

            
			// event dispatching to children
			bool result = false;
			for (std::vector<Sprite*>::const_reverse_iterator it = _children.rbegin(); it != _children.rend(); ++it)
			{
				MenuSprite* menuSprite = (MenuSprite*)(*it);
				
				// transmit event to child
				result = menuSprite->onTouch(localevent);
				// if event has been consumed by the child we stop to dispatch it
				if( result == true )
				{
					break;
				}
			}
			return result;
		}
		
		
		
		
		TouchEvent MenuSprite::convertTouchEventCoordinates( TouchEvent event )
		{
			// get parent size
            
            float screenScale = 1.0f;
            
            if (isScaledToFitDeviceResolution())
            {
				screenScale = utils::scaling::pointToPixel();
            }
            
            
			Size parentSize(0.0f, 0.0f);
			if( getParent() == nullptr )
			{
				// parent is the screen
				px::tools::size screenSizeInPixels = px::tools::device::getScreenSizeInPixels(px::tools::device::ScreenOrientation::LANDSCAPE);
				// compute size of screen in game points
				parentSize.setWidth(screenSizeInPixels.width * utils::scaling::pixelToPoint());
				parentSize.setHeight(screenSizeInPixels.height * utils::scaling::pixelToPoint());
			}
			else
			{
				// parent is an other MenuSprite object
				// parentSize = getParent()->getContentSize();
                
                if (((MenuSprite*)getParent())->isScaledToFitDeviceResolution())
                {
                    parentSize.set(getParent()->getContentSize().getWidth() * utils::scaling::pointToPixel(), getParent()->getContentSize().getHeight() * utils::scaling::pointToPixel());
                }
                else
                {
                    parentSize = getParent()->getContentSize();
                }
			}
            
			Point anchorPointInParent = MenuSprite::convertRelativePositionIntoAnchorPoint(_relativePosition);
            
            Point anchorPositionInParent = Point(anchorPointInParent.getX2D() * parentSize.getWidth()  + _position.getX2D(),
												 anchorPointInParent.getY2D() * parentSize.getHeight() + _position.getY2D());
            
            //printf("anchor point in parent: %.2f - %.2f\n",anchorPointInParent.getX2D(),anchorPointInParent.getY2D());
            //printf("anchor position in parent: %.2f - %.2f\n",anchorPositionInParent.getX2D(),anchorPositionInParent.getY2D());
            
			Point positionOfBottomLeftCornerInParent = anchorPositionInParent - Point(_anchor.getX2D() * _contentSize.getWidth() * getScale().getX2D() * screenScale,
																					  _anchor.getY2D() * _contentSize.getHeight() * getScale().getY2D()* screenScale);
            
			
			event.setX( event.getX() - positionOfBottomLeftCornerInParent.getX2D() );
			event.setY( event.getY() - positionOfBottomLeftCornerInParent.getY2D() );
			
			return event;
		}
		
		
		
#pragma mark - Accessors -
		
        
        
		px::tools::Rect MenuSprite::getBoundingBox()
		{
			px::tools::Rect result;
			
            
            // handle scale factor to fit screen resolution
            
            float screenScale = 1.0f;
            
            if (isScaledToFitDeviceResolution())
            {
                screenScale = utils::scaling::pointToPixel();
            }
            
            
			// we compute the in-parent position of the
			// bottom-left corner of the menusprite
			
			// parent size in game points
			Size parentContentSize;
			if( getParent() == nullptr )
			{
				// parent is the screen
				px::tools::size screenSizeInPixels = px::tools::device::getScreenSizeInPixels(px::tools::device::ScreenOrientation::LANDSCAPE);
				// compute size of screen in game points
				parentContentSize.setWidth(screenSizeInPixels.width * utils::scaling::pixelToPoint());
				parentContentSize.setHeight(screenSizeInPixels.height * utils::scaling::pixelToPoint());
			}
			else
			{
				// parent is an other MenuSprite object
                
                if (((MenuSprite*)getParent())->isScaledToFitDeviceResolution())
                {
                    parentContentSize.set(getParent()->getContentSize().getWidth() * screenScale, getParent()->getContentSize().getHeight() * screenScale);
                }
                else
                {
                    parentContentSize = getParent()->getContentSize();
                }
			}
			
			// distance from parent's bottom left corner to curent's position
			Point anchorInParent = MenuSprite::convertRelativePositionIntoAnchorPoint(_relativePosition);
			Point positionInParent = getPosition();
            
            // a-> position of anchor in parent from its bottom left origin
			Point a = Point(anchorInParent.getX2D() * parentContentSize.getWidth() + positionInParent.getX2D(),
							anchorInParent.getY2D() * parentContentSize.getHeight()+ positionInParent.getY2D());
			
            
            
            
            
            // distance from current's position to current's bottom left corner
			Point b = Point(-_anchor.getX2D() * _contentSize.getWidth() * screenScale,
							-_anchor.getY2D() * _contentSize.getHeight() * screenScale);
			
			// distance from parent's bottom left corner to current's bottom left corner
			
			Point c = a + b;
			
			
			// define the result variable
			result.setX(c.getX2D());
			result.setY(c.getY2D());
            
			result.setWidth(_contentSize.getWidth() * screenScale);
			result.setHeight(_contentSize.getHeight() * screenScale);
            

			
			return result;
		}
		
		
		
#pragma mark - Modifiers -
		
		
	}
}




