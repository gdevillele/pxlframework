//
//  Slider.cpp
//  pxlframework
//
//  Created by Gaëtan de Villèle on 11/22/13.
//
//


#include "Slider.h"

// pxlframework
#include "SliderListener.h"


namespace px
{
	namespace engine
	{
		float Slider::guiSliderTouchMargin = 0.0f;

#pragma mark - Instance building functions -
		
		Slider* Slider::newSlider(const std::string& backgroundTextureName,
								  const std::string& buttonTextureName,
								  const MenuSprite::RelativePosition relativePosition,
								  const MenuSprite::RelativePosition anchor,
								  const Point& position,
								  const float sliderPercentage,
								  const float sliderWidth)
		{
			Slider* result = new Slider();
			
			// define MenuSprite specific attributes
			result->setTextureName(backgroundTextureName);
			result->setRelativePosition(relativePosition);
			result->setAnchor(MenuSprite::convertRelativePositionIntoAnchorPoint(anchor));
			result->setPosition(Point(position.getX2D(), position.getY2D()));
			
			// define Slider specific attributes
			// set the orientation value
			result->_orientation = Orientation::HORIZONTAL;
			// store the width (we need it and we don't have it
			// because the renderer instance has not been created yet)
			result->setContentSize(Size(sliderWidth, 0.0f));
			// add slider button and define percentage
			result->createSliderButton(buttonTextureName, sliderPercentage);
			
			return result;
		}
		
		
		Slider* Slider::newVerticalSlider(const std::string& backgroundTextureName,
										  const std::string& buttonTextureName,
										  const RelativePosition relativePosition,
										  const RelativePosition anchor,
										  const Point& position,
										  const float sliderPercentage,
										  const float sliderHeight)
		{
			Slider* result = new Slider();
			
			// define MenuSprite specific attributes
			result->setTextureName(backgroundTextureName);
			result->setRelativePosition(relativePosition);
			result->setAnchor(MenuSprite::convertRelativePositionIntoAnchorPoint(anchor));
			result->setPosition(Point(position.getX2D(), position.getY2D()));
			
			// define Slider specific attributes
			// set the orientation value
			result->_orientation = Orientation::VERTICAL;
			// store the height (we need it and we don't have it
			// because the renderer instance has not been created yet)
			result->setContentSize(Size(0.0f, sliderHeight));
			// add slider button and define percentage
			result->createSliderButton(buttonTextureName, sliderPercentage);
			
			return result;
		}
		
		
		
#pragma mark - Constructor / Destructor -
		
		Slider::Slider() : MenuSprite(),
		_button(nullptr),
		_downEventPosition(0.0f, 0.0f),
		_downEventPercentage(0.0f),
		_percentage(0.0f),
		_listener(nullptr)
		{}
		
		
		
		/*virtual*/
		Slider::~Slider()
		{}
		
		
		
#pragma mark - Public Methods -
		
		
		
		
		
		
		
#pragma mark - Inherited Methods -
		
		bool Slider::onTouch( TouchEvent event )
		{
			bool result = false;
			
			if (_orientation == Orientation::HORIZONTAL)
			{
				if (_button != nullptr)
				{
					// move touch event into slider inner coordinates
					event = convertTouchEventCoordinates(event);
					// get event data
					const TouchEvent::Type eventType = event.getType();
					const float eventX = event.getX();
					const float eventY = event.getY();
					
					if( eventType == TouchEvent::Type::DOWN )
					{
						if( _state == MenuSprite::State::NORMAL )
						{
							// test if touch event is on the slider button
							
							// get the button's bounding box (in the slider inner coordinates)
							px::tools::Rect buttonBB = _button->getBoundingBox();
							
							// add the GUI touch margin to the bounding box
							buttonBB.setX(buttonBB.getX() - guiSliderTouchMargin);
							buttonBB.setY(buttonBB.getY() - guiSliderTouchMargin);
							buttonBB.setWidth(buttonBB.getWidth() + 2*guiSliderTouchMargin);
							buttonBB.setHeight(buttonBB.getHeight() + 2*guiSliderTouchMargin);
							
							if(eventX > buttonBB.getX() && eventX < buttonBB.getX()+buttonBB.getWidth() &&
							   eventY > buttonBB.getY() && eventY < buttonBB.getY()+buttonBB.getHeight())
							{
								_state = MenuSprite::State::PRESSED;
								_downEventPosition.set2D(eventX, eventY);
								_downEventPercentage = _percentage;
								result = true;
							}
						}
					}
					else if( eventType == TouchEvent::Type::MOVE )
					{
						if( _state == MenuSprite::State::PRESSED )
						{
							// compute the new slider percentage
							Point deltaPosition = Point(eventX, eventY) - _downEventPosition;
							float deltaPercentage = deltaPosition.getX2D() / _contentSize.getWidth();
							float newPercentage = _downEventPercentage + deltaPercentage;
							if(newPercentage < 0.0f)
								newPercentage = 0.0f;
							else if (newPercentage > 1.0f)
								newPercentage = 1.0f;
							_percentage = newPercentage;
							// compute the new slider button position
							_button->setPosition(Point(0.0f + _contentSize.getWidth() * _percentage, 0.0f));
							
							_button->setChanged(true);
							// consume the touch event
							result = true;
							
							if ( _listener != nullptr )
							{
								_listener->onPercentageChanged(_percentage);
							}
						}
						
					}
					else if ( eventType == TouchEvent::Type::UP )
					{
						if( _state == MenuSprite::State::PRESSED )
						{
							_state = MenuSprite::State::NORMAL;
							
							if ( _listener != nullptr )
							{
								_listener->onDone(_percentage);
							}
						}
					}
				}
			}
			else if (_orientation == Orientation::VERTICAL)
			{
				if (_button != nullptr)
				{
					// move touch event into slider inner coordinates
					event = convertTouchEventCoordinates(event);
					// get event data
					const TouchEvent::Type eventType = event.getType();
					const float eventX = event.getX();
					const float eventY = event.getY();
					
					if( eventType == TouchEvent::Type::DOWN )
					{
						if( _state == MenuSprite::State::NORMAL )
						{
							// test if touch event is on the slider button
							
							// get the button's bounding box (in the slider inner coordinates)
							px::tools::Rect buttonBB = _button->getBoundingBox();
							
							if(eventX > buttonBB.getX() && eventX < buttonBB.getX()+buttonBB.getWidth() &&
							   eventY > buttonBB.getY() && eventY < buttonBB.getY()+buttonBB.getHeight())
							{
								_state = MenuSprite::State::PRESSED;
								_downEventPosition.set2D(eventX, eventY);
								_downEventPercentage = _percentage;
								result = true;
							}
						}
					}
					else if( eventType == TouchEvent::Type::MOVE )
					{
						if( _state == MenuSprite::State::PRESSED )
						{
							// compute the new slider percentage
							Point deltaPosition = Point(eventX, eventY) - _downEventPosition;
							float deltaPercentage = deltaPosition.getY2D() / _contentSize.getHeight();
							float newPercentage = _downEventPercentage + deltaPercentage;
							if(newPercentage < 0.0f)
								newPercentage = 0.0f;
							else if (newPercentage > 1.0f)
								newPercentage = 1.0f;
							_percentage = newPercentage;
							// compute the new slider button position
							_button->setPosition(Point(0.0f, 0.0f + _contentSize.getHeight() * _percentage));
							
							_button->setChanged(true);
							// consume the touch event
							result = true;
							
							if ( _listener != nullptr )
							{
								_listener->onPercentageChanged(_percentage);
							}
						}
						
					}
					else if ( eventType == TouchEvent::Type::UP )
					{
						if( _state == MenuSprite::State::PRESSED )
						{
							_state = MenuSprite::State::NORMAL;
							
							if ( _listener != nullptr )
							{
								_listener->onDone(_percentage);
							}
						}
					}
				}
			}
			
			return result;
		}
		
		
		
		
		
#pragma mark - Private Methods -
		
		void Slider::createSliderButton(const std::string& buttonTextureName,
										const float percentage)
		{
			if (_orientation == Orientation::HORIZONTAL)
			{
				_button = MenuSprite::newMenuSpriteWithTexture(buttonTextureName,
															   MenuSprite::RelativePosition::LEFT,
															   MenuSprite::RelativePosition::CENTER,
															   Point(0.0f, 0.0f));
			}
			else if (_orientation == Orientation::VERTICAL)
			{
				_button = MenuSprite::newMenuSpriteWithTexture(buttonTextureName,
															   MenuSprite::RelativePosition::BOTTOM,
															   MenuSprite::RelativePosition::CENTER,
															   Point(0.0f, 0.0f));
			}
			addChild(_button);
			setPercentage(percentage);
		}
		
		
		
		void Slider::setPercentage(const float percentage)
		{
			if(_button != nullptr)
			{
				Point newPosition;
				if (_orientation == Orientation::HORIZONTAL)
				{
					newPosition = Point(getContentSize().getWidth() * percentage, 0.0f);
				}
				else if (_orientation == Orientation::VERTICAL)
				{
					newPosition = Point(0.0f, getContentSize().getHeight() * percentage);
				}
				
				_percentage = percentage;
				_button->setPosition(newPosition);
				_button->setChanged(true);
			}
		}
		
		
		
		void Slider::setListener(SliderListener* listener)
		{
			_listener = listener;
		}
		
		
		void Slider::unsetListener()
		{
			_listener = nullptr;
		}
	}
}




