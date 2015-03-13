//
//  Toggle.cpp
//  pxlframework
//
//  Created by Axel Guilmin on 3/5/14.
//
//


#include "Toggle.h"


namespace px
{
	namespace engine
	{
		
#pragma mark - Factory -
		
		Toggle* Toggle::newToggleWithTexture(const std::string& texture_name,
											 const MenuSprite::RelativePosition relativePosition,
											 const MenuSprite::RelativePosition anchor,
											 const Point& position,
											 bool on,
											 FunctionPointerHandler* target,
											 px::FunctionPointerButtonCallback selector,
											 const std::string& labelOn,
											 const std::string& labelOff,
                                             const std::string& font,
                                             const float fontSize,
                                             bool isBitmap)
		{
			Toggle* result = new Toggle();
			
			// define MenuSprite specific attributes
			result->setTextureName(texture_name);
			result->setFrameInfos(2, 2, 1);
			result->setRelativePosition(relativePosition);
			result->setAnchor(MenuSprite::convertRelativePositionIntoAnchorPoint(anchor));
			result->setPosition( Point(position.getX2D(), position.getY2D()) );
			
			// define Toggle specific stuff
			
			result->_labelOn = labelOn;
			result->_labelOff = labelOff;
			
			result->addLabel("-", {255,255,255,255}, font,fontSize,isBitmap);
			
			
			result->setTarget(target);
			result->setSelector(selector);
			if(on)
				result->setOn();
			else
				result->setOff();
			
			return result;
		}
		
		
		
#pragma mark - Constructor / Destructor -
		
		Toggle::Toggle() : Button::Button(),
		_on(false)
		{
		}
		
		
		/*virtual*/
		Toggle::~Toggle()
		{}
		
		
		
#pragma mark - Methods -
		// @todo industrialize with Button::onTouch()
		bool Toggle::onTouch( TouchEvent event )
		{
			// if the Toggle is disabled
			// we ignore this touch event
			if( _state == State::DISABLED )
			{
				return false;
			}
			
			// if the touch event is a CANCEL event
			// we just release the Toggle and return
			// without consuming the touch event
			if (event.getType() == TouchEvent::Type::CANCEL)
			{
				release();
				return false;
			}
			
			bool result = false;
			
			// get event data
			const TouchEvent::Type eventType = event.getType();
			const float eventX = event.getX();
			const float eventY = event.getY();
			
			// get this Toggle's bounding box
			px::tools::Rect bb = getBoundingBox();
			
			// add the GUI touch margin to the bounding box
            
			bb.setX(bb.getX() - guiButtonTouchMargin);
			bb.setY(bb.getY() - guiButtonTouchMargin);
			bb.setWidth(bb.getWidth() + 2*guiButtonTouchMargin);
			bb.setHeight(bb.getHeight() + 2*guiButtonTouchMargin);
			
			// test if touch event is on the Toggle
			if(eventX > bb.getX() && eventX < bb.getX()+bb.getWidth() &&
			   eventY > bb.getY() && eventY < bb.getY()+bb.getHeight())
			{
				// event is on the Toggle
				// in this case we test only touch DOWN and UP
				if( eventType == TouchEvent::Type::DOWN )
				{
					// we push the Toggle
					press();
					// we consume the touch event
					result = true;
				}
				else if( eventType == TouchEvent::Type::UP )
				{
					// Toggle receives a touch up event on it
					// but it may be not pushed at this time
					// if it was pushed, it's a click action
					// if it wasn't it does nothing
					if( _state == State::PRESSED )
					{
						if(_on)
							setOff();
						else
							setOn();
						// this is a click action
						clickCallback();
						// we consume the touch event
						result = true;
					}
					// in both cases, Toggle isn't pushed anymore
					release();
				}
			}
			else
			{
				// event is not on this Toggle object
				if( eventType == TouchEvent::Type::UP )
				{
					// Toggle is no more down, it's a click cancel action
					// PXLLOG("Toggle touch UP cancel");
					release();
					// we do not consume this event because it wasn't on the Toggle
				}
			}
			return result;
		}
		
		
		
		void Toggle::addChild( Sprite* child )
		{
			// a Toggle object cannot have children
			PXLLOG("[Toggle::addChild] this method do nothing, please don't use it");
			PXL_ASSERT(false);
		}
		
	}
}




