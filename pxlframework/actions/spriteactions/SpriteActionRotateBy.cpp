//
//  SpriteActionRotateBy.cpp
//  pxlframework
//
//  Created by Axel Guilmin on 12/2/13.
//
//


#include "SpriteActionRotateBy.h"


// pxlframework
#include "Sprite.h"


namespace px
{
	namespace engine
	{
		
		/*static*/ SpriteActionRotateBy* SpriteActionRotateBy::withDuration(const Tick::Duration duration, const Sprite::Angle angle)
		{
			SpriteActionRotateBy* action = new SpriteActionRotateBy();
			
			if( ! action->init(duration, angle))
			{
				delete action;
				action = NULL;
			}
			
			return action;
		}
		
		/*virtual*/ SpriteActionRotateBy::~SpriteActionRotateBy()
		{
		}
		
		bool SpriteActionRotateBy::init(const Tick::Duration duration, const Sprite::Angle angle)
		{
			if(Action::init(duration))
			{
				_by = angle;
				return true;
			}
			
			return false;
		}
		
		/*virtual*/ void SpriteActionRotateBy::start(Action_Receiver *receiver)
		{
			//PXL_ASSERT( dynamic_cast<Sprite*>(receiver) != nullptr );
			
			Action::start(receiver);
			_receiver = static_cast<Sprite*>(receiver);
			// @todo sprite may be NULL
			_origin = _receiver->getRotation();
		}
		
		/*virtual*/ void SpriteActionRotateBy::update(const Percentage time)
		{
			Sprite::Angle newAngle = _origin + _by * time;
			
			_receiver->setRotation(newAngle);
		}
		
		SpriteActionRotateBy::SpriteActionRotateBy() : Action(),
		_origin(0.0f),
		_by(0.0f),
		_receiver(nullptr)
		{
			
		}
	}
}




