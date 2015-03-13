//
//  LabelIncr.cpp
//  pxlframework
//
//  Created by Adrien Duermaël on 3/17/14.
//
//


#include "LabelIncr.h"

// pxlframework
#include "SoundManagerInterface.h"


namespace px
{
	namespace engine
	{
		
		
#pragma mark - Construction functions -
		
		LabelIncr* LabelIncr::newLabelIncr(const MenuSprite::RelativePosition relativePosition,
										   const MenuSprite::RelativePosition anchor,
										   const Point& position,
										   int number,
										   const std::string& font,
										   Tick::Duration maximumTotalTime,
										   int minimumUpdateValue)
		{
			LabelIncr* result = new LabelIncr();
			
			// define MenuSprite specific attributes
			result->setRelativePosition(relativePosition);
			result->setAnchor(MenuSprite::convertRelativePositionIntoAnchorPoint(anchor));
			result->setPosition(Point(position.getX2D(), position.getY2D()));
			
			// define Label specific attributes
			result->setNumber(number);
			result->_numberDisplayed = number;
			
			result->setText(tostr(number));
			result->setFont(font);
			
			result->setMaximumTotalTime(maximumTotalTime);
			result->setMinimumUpdateValue(minimumUpdateValue);
			
			return result;
		}
        
		
		
		LabelIncr* LabelIncr::newLabelIncr(const Point& anchor,
										   const Point& position,
										   int number,
										   const std::string& font,
										   Tick::Duration maximumTotalTime,
										   int minimumUpdateValue)
		{
			LabelIncr* result = new LabelIncr();
			
			// define MenuSprite specific attributes
			result->setAnchor(anchor);
			result->setPosition(position);
			
			// define Label specific attributes
			result->setNumber(number);
			result->_numberDisplayed = number;
			
			result->setText(tostr(number));
			result->setFont(font);
			
			result->setMaximumTotalTime(maximumTotalTime);
			result->setMinimumUpdateValue(minimumUpdateValue);
			
			
			return result;
		}
		
		
#pragma mark - Tick
		
		/* virtual */ void LabelIncr::tick(const Tick::Duration dt)
		{
			if (_numberDisplayed != _number)
			{
				int diff = _number - _numberDisplayed;
				
				int framesRemaining = (int)(_timeRemaining / dt);
				
				if (framesRemaining <= 0)
				{
					_numberDisplayed = _number;
				}
				else
				{
					float add = (float)diff / (float)framesRemaining;
					
					if (fabsf(add) < _minimumUpdateValue)
					{
						if (add < 0)
							add = -_minimumUpdateValue;
						else
							add = _minimumUpdateValue;
					}
					
					_numberDisplayed += (int)add;
                    
                    if (!_sfx.empty())
                        px::tools::SoundManagerInterface::playSoundEffect(_sfx, true);
				}
				
				_timeRemaining -= dt;
				setText(tostr(_numberDisplayed));
                
                if (_numberDisplayed == _number)
                {
                    if (!_sfx.empty())
                        px::tools::SoundManagerInterface::stopSoundEffect(_sfx);
                }
			}
		}
		
		
#pragma mark - Constructor / Destructor -
		
		LabelIncr::LabelIncr() : Label(),
        _sfx("")
		{
			setType(Sprite::Type::LABEL);
		}
		
		/*virtual*/
		LabelIncr::~LabelIncr()
		{}
	}
}




