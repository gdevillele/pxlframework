//
//  SpriteActionScaleTo.cpp
//  pxlframework
//
//  Created by Axel Guilmin on 12/2/13.
//
//


#include "SpriteActionScaleTo.h"


// pxlframework
#include "Sprite.h"


namespace px
{
	namespace engine
	{
		/*static*/ SpriteActionScaleTo* SpriteActionScaleTo::withDuration(const Tick::Duration duration, const Sprite::Scale scale)
		{
			SpriteActionScaleTo* action = new SpriteActionScaleTo();
			
			if( ! action->init(duration, scale))
			{
				delete action;
				action = NULL;
			}
			
			return action;
		}
		
		/*virtual*/ SpriteActionScaleTo::~SpriteActionScaleTo()
		{
		}
		
		bool SpriteActionScaleTo::init(const Tick::Duration duration, const Sprite::Scale scale)
		{
			if(Action::init(duration))
			{
				_to = scale;
				return true;
			}
			
			return false;
		}
		
		/*virtual*/ void SpriteActionScaleTo::start(Action_Receiver *receiver)
		{
			//PXL_ASSERT( dynamic_cast<Sprite*>(receiver) != nullptr );
			
			Action::start(receiver);
			_receiver = static_cast<Sprite*>(receiver);
			// @todo sprite may be NULL
			_origin = _receiver->getScale();
		}
		
		/*virtual*/ void SpriteActionScaleTo::update(const Percentage time)
		{
			Sprite::Scale newScale = _origin * (1.0f - time) + _to * time;
			
			_receiver->setScale(newScale);
		}
		
		SpriteActionScaleTo::SpriteActionScaleTo() : Action(),
		_origin(1.0f, 1.0f),
		_to(1.0f, 1.0f),
		_receiver(nullptr)
		{
			
		}
	}
}




