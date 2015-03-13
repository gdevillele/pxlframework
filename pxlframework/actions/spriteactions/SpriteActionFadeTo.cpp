//
//  SpriteActionFadeTo.cpp
//  pxlframework
//
//  Created by Adrien Duermaël on 12/3/13.
//
//


#include "SpriteActionFadeTo.h"


namespace px
{
	namespace engine
	{
		
		/*static*/ SpriteActionFadeTo* SpriteActionFadeTo::withDuration(const Tick::Duration duration, const float opacity)
		{
			SpriteActionFadeTo* action = new SpriteActionFadeTo();
			
			if( ! action->init(duration, opacity))
			{
				delete action;
				action = NULL;
			}
			
			return action;
		}
		
		/*virtual*/ SpriteActionFadeTo::~SpriteActionFadeTo()
		{
		}
		
		bool SpriteActionFadeTo::init(const Tick::Duration duration, const float opacity)
		{
			if(Action::init(duration))
			{
				_to = opacity;
				return true;
			}
			
			return false;
		}
		
		/*virtual*/ void SpriteActionFadeTo::start(Action_Receiver *receiver)
		{
			//PXL_ASSERT( dynamic_cast<Sprite*>(receiver) != nullptr );
			
			Action::start(receiver);
			_receiver = static_cast<Sprite*>(receiver);
			// @todo sprite may be NULL
			_origin = _receiver->getOpacity();
		}
		
		/*virtual*/ void SpriteActionFadeTo::update(const Percentage time)
		{
			float newOpacity = _origin * (1.0f - time) + _to * time;
			_receiver->setOpacity(newOpacity);
		}
		
		SpriteActionFadeTo::SpriteActionFadeTo() : Action(),
		_origin(0.0f),
		_to(0.0f)
		{
			
		}
	}
}




