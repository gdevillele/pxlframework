//
//  SpriteActionTintTo.cpp
//  pxlframework
//
//  Created by Axel Guilmin on 12/6/13.
//
//


#include "SpriteActionTintTo.h"


// pxlframework
#include "Sprite.h"


namespace px
{
	namespace engine
	{
		
		/*static*/ SpriteActionTintTo* SpriteActionTintTo::withDuration(const Tick::Duration duration, const Color scale)
		{
			SpriteActionTintTo* action = new SpriteActionTintTo();
			
			if( ! action->init(duration, scale))
			{
				delete action;
				action = NULL;
			}
			
			return action;
		}
		
		/*virtual*/ SpriteActionTintTo::~SpriteActionTintTo()
		{
		}
		
		bool SpriteActionTintTo::init(const Tick::Duration duration, const Color scale)
		{
			if(Action::init(duration))
			{
				_to = scale;
				return true;
			}
			
			return false;
		}
		
		/*virtual*/ void SpriteActionTintTo::start(Action_Receiver *receiver)
		{
			//PXL_ASSERT( dynamic_cast<Sprite*>(receiver) != nullptr );
			
			Action::start(receiver);
			_receiver = static_cast<Sprite*>(receiver);
			// @todo sprite may be NULL
			_origin = _receiver->getColor();
		}
		
		/*virtual*/ void SpriteActionTintTo::update(const Percentage time)
		{
			Color newColor({
				(uint8_t)((float)_origin.r * (1.0f - time) + (float)_to.r * time),
				(uint8_t)((float)_origin.g * (1.0f - time) + (float)_to.g * time),
				(uint8_t)((float)_origin.b * (1.0f - time) + (float)_to.b * time),
				(uint8_t)((float)_origin.a * (1.0f - time) + (float)_to.a * time)
			});
			
			_receiver->setColor(newColor);
		}
		
		SpriteActionTintTo::SpriteActionTintTo() : Action(),
		_origin(),
		_to(),
		_receiver(nullptr)
		{
			
		}
	}
}




