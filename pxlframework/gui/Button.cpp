//
//  Button.cpp
//  pxlframework
//
//  Created by Adrien Duermaël on 8/21/13.
//
//


#include "Button.h"


// pxlframework
#include "ActionSequence.h"
#include "SpriteActionScaleTo.h"
#include "ActionRepeatForever.h"
// px::tools
#include <SoundManagerInterface.h>


namespace px
{
	namespace engine
	{
#pragma mark - Factory -

        float Button::guiButtonTouchMargin = 0.0f;
        float Button::buttonBreathingSize = 5.0f;
        float Button::buttonIncreaseSizeWhenTouched = 3.0f;
		
		Button* Button::newButton(const std::string& textureName,
								  const MenuSprite::RelativePosition relativePosition,
								  const MenuSprite::RelativePosition anchor,
								  const Point& position,
								  FunctionPointerHandler* target,
								  px::FunctionPointerButtonCallback selector)
		{
			Button* result = new Button();
			
			// define MenuSprite specific attributes
			result->setTextureName(textureName);
			result->setRelativePosition(relativePosition);
			result->setAnchor(MenuSprite::convertRelativePositionIntoAnchorPoint(anchor));
			result->setPosition(Point(position.getX2D(), position.getY2D()));
			
			// define Button specific stuff
			result->setTarget(target);
			result->setSelector(selector);
			
			return result;
		}
		
		/*static*/ Button* Button::newButton(MenuSprite *content,
											 FunctionPointerHandler* target,
											 px::FunctionPointerButtonCallback selector)
		{
			PXL_ASSERT(content != nullptr);
			
			Button* result = new Button();
			
			result->setType(px::engine::Sprite::Type::NOTEXTURE);
			
			// content properties -> button properties
			result->setRelativePosition(content->getRelativePosition());
			result->setAnchor(content->getAnchor());
			result->setPosition(content->getPosition());
			result->setContentSize(content->getContentSize());
			
			// reset content properties, and add it
			content->setRelativePosition(MenuSprite::RelativePosition::CENTER);
			content->setAnchor(0.5f, 0.5f);
			content->setPosition({0.0f, 0.0f});
			
			result->MenuSprite::addChild(content);
			
			// define Button specific stuff
			result->setTarget(target);
			result->setSelector(selector);
			
			return result;
		}
		
		/* virtual */ void Button::setContentSize(const Size size)
		{
			Sprite::setContentSize(size);
			
			if (_important)
			{
				animateBreathing();
			}
		}
		
		
		
#pragma mark - Constructor / Destructor -
		
		Button::Button() : MenuSprite::MenuSprite(),
		_label(nullptr),
		_target(nullptr),
		_selector(nullptr),
		_userData(nullptr),
        _userDataInt(0),
		_important(false),
		_enabled(true),
        _target_touch_down(nullptr),
        _selector_touch_down(nullptr),
        _target_touch_up(nullptr),
        _selector_touch_up(nullptr)
		{}
		
		
		
		/*virtual*/
		Button::~Button()
		{}
		
		
		
#pragma mark - Methods -
		
        void Button::touchDownCallback()
        {
            if(!_enabled)
                return;
            
            if (_target_touch_down != nullptr && _selector_touch_down != nullptr)
            {
                (_target_touch_down->*_selector_touch_down)(this);
            }
        }
        
        
        void Button::touchUpCallback()
        {
            if(!_enabled)
                return;
            
            if (_target_touch_up != nullptr && _selector_touch_up != nullptr)
            {
                (_target_touch_up->*_selector_touch_up)(this);
            }
        }
        
        
		void Button::clickCallback()
		{
			if(!_enabled)
				return;
            
            //px::tools::SoundManagerInterface::playSoundEffect(_important ? "buttonTapPositive.wav" : "buttonTap.wav");
			
			// if the target is null, we trigger the default callback
			if (_target != nullptr && _selector != nullptr)
			{
				(_target->*_selector)(this);
			}
			else
			{
				defaultCallback();
			}
		}
		
		
		
		void Button::defaultCallback()
		{
			//PXLLOG("Button::defaultCallback (button object : %p)", this);
		}
		
		
		
		bool Button::onTouch( TouchEvent event )
		{
			// if the button is disabled
			// we ignore this touch event
			if( _state == State::DISABLED )
			{
				return false;
			}
			
			// if the touch event is a CANCEL event
			// we just release the button and return
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
			
			// get this button's bounding box
			px::tools::Rect bb = getBoundingBox();
            
			// add the GUI touch margin to the bounding box
			bb.setX(bb.getX() - guiButtonTouchMargin);
			bb.setY(bb.getY() - guiButtonTouchMargin);
			bb.setWidth(bb.getWidth() + 2*guiButtonTouchMargin);
			bb.setHeight(bb.getHeight() + 2*guiButtonTouchMargin);
			
			// test if touch event is on the button
			if(eventX > bb.getX() && eventX < bb.getX()+bb.getWidth() &&
			   eventY > bb.getY() && eventY < bb.getY()+bb.getHeight())
			{
				// event is on the button
				// in this case we test only touch DOWN and UP
				if( eventType == TouchEvent::Type::DOWN )
				{
					// we push the button
					press();

					// we consume the touch event
					result = true;
				}
				else if( eventType == TouchEvent::Type::UP )
				{
					// button receives a touch up event on it
					// but it may be not pushed at this time
					// if it was pushed, it's a click action
					// if it wasn't it does nothing
					
                    
                    if( _state == State::PRESSED )
					{
						// this is a click action
                        
                        release();
						clickCallback();
						// we consume the touch event
						result = true;
					}
                    else
                    {
                        // in both cases, button isn't pushed anymore
                        release();
                    }
				}
			}
			else
			{
				// event is not on this button object
				if( eventType == TouchEvent::Type::UP )
				{
					// button is no more down, it's a click cancel action
					// PXLLOG("button touch UP cancel");
					release();
					// we do not consume this event because it wasn't on the button
				}
			}
			return result;
		}
		
		
		
#pragma mark - Accessors -
		
		const std::string Button::getText() const
		{
			if( _label != nullptr )
				return _label->getText();
			else
				return std::string();
		}
		
		
		
		
		
#pragma mark - Modifiers -
		
        void Button::addLabel(const std::string& text, const Color color, const std::string& font,const float fontSize,bool isBitmap)
		{
			if (_label == nullptr)
			{
				_label = Label::newLabel(MenuSprite::RelativePosition::CENTER,
										 MenuSprite::RelativePosition::CENTER,
										 Point(0.0f, 0.0f), text, font);
				_label->setColor(color);
                _label->setFontSize(fontSize);
                
                if (isBitmap)
                {
                    _label->setBitmap();
                }
                
				Sprite::addChild(_label);
			}
			else
			{
				// button already have a label, so we log a warning
				PXLLOG("[Button::addLabel] button already have a Label, please use modifiers methods instead");
				PXL_ASSERT(false);
			}
		}
		
		
		
		void Button::setLabelText( const std::string& text )
		{
			if (_label != nullptr)
			{
				// if it already has a Label, we update it
				_label->setText(text);
			}
		}
		
		
		
		void Button::setLabelColor(const Color color)
		{
			if (_label != nullptr)
			{
				// if it already has a Label, we update it
				_label->setColor(color);
			}
		}
		
		
		
		void Button::setTarget(FunctionPointerHandler* target)
		{
			_target = target;
		}
		
		
		void Button::setSelector(px::FunctionPointerButtonCallback selector)
		{
			_selector = selector;
		}
        
        
        void Button::setTouchDownTargetAndSelector(FunctionPointerHandler* target, px::FunctionPointerButtonCallback selector)
        {
            _selector_touch_down = selector;
            _target_touch_down = target;
        }
        
        void Button::setTouchUpTargetAndSelector(FunctionPointerHandler* target, px::FunctionPointerButtonCallback selector)
        {
            _selector_touch_up = selector;
            _target_touch_up = target;
        }
        
        
		
		void Button::disable()
		{
			_enabled = false;
		}
		
		void Button::enable()
		{
			_enabled = true;
			
			// Restart the breathing animation if needed
			if (_important)
				animateBreathing();
		}
		
		
		void Button::setImportant(bool important)
		{
			_important = important;
			if (_important)
			{
				animateBreathing();
			}
		}
		
		
		
#pragma mark - Private Methods -
		
		void Button::press()
		{
            touchDownCallback();
            
			if (getState() == State::NORMAL && _enabled)
			{
				setState(State::PRESSED);
				setChanged(true);
                
                deleteAllActions();
                
				animatePressed();
			}
		}
		
		
		
		void Button::release()
		{
            touchUpCallback();
            
			if (getState() == State::PRESSED && _enabled)
			{
				setState(State::NORMAL);
				setChanged(true);
                
                deleteAllActions();
                
				animateReleased();
			}
		}
		
		
		
		void Button::animateBreathing()
		{
			if(!_enabled)
				return;
			
			float s = std::sqrt(std::pow(this->getContentSize().getWidth(),2.0) + std::pow(this->getContentSize().getHeight(),2.0));
			
			if (s == 0) return;
			
			float ratio = 1.0f + (1.0f - (s / (s + buttonBreathingSize))); // increase size by 20 pts
			
			deleteAllActions();
			
			runAction(ActionRepeatForever::withAction(ActionSequence::withActions(SpriteActionScaleTo::withDuration(0.5f, ratio),
																				  SpriteActionScaleTo::withDuration(0.5f, 1.0f))));
		}
		
		
		
		void Button::animatePressed()
		{
			if(!_enabled)
				return;
			
			deleteAllActions();
			
			float s = std::sqrt(std::pow(this->getContentSize().getWidth(),2.0) + std::pow(this->getContentSize().getHeight(),2.0));
			float ratio = 1.0f + (1.0f - (s / (s + buttonIncreaseSizeWhenTouched))); // increase size by 20 pts
			
			runAction(SpriteActionScaleTo::withDuration(0.03f, ratio));
		}
		
		
		
		void Button::animateReleased()
		{
			if(!_enabled)
				return;
			
			if (_important)
			{
				animateBreathing();
			}
			else
			{
				deleteAllActions();
				runAction(SpriteActionScaleTo::withDuration(0.03f, 1.0f));
			}
		}
	}
}




