//
//  SpriteActionMoveTo.cpp
//  pxlframework
//
//  Created by Adrien Duermaël on 1/3/14.
//
//


#include "SpriteActionMoveTo.h"


namespace px
{
	namespace engine
	{
		
		/*static*/ SpriteActionMoveTo* SpriteActionMoveTo::withDuration(const Tick::Duration duration, const Point to)
		{
			SpriteActionMoveTo* action = new SpriteActionMoveTo();
			
			if( ! action->init(duration, to))
			{
				delete action;
				action = nullptr;
			}
			
			return action;
		}
		
		/*virtual*/ SpriteActionMoveTo::~SpriteActionMoveTo()
		{
		}
		
		bool SpriteActionMoveTo::init(const Tick::Duration duration, const Point to)
		{
			if(Action::init(duration))
			{
				_to = to;
				return true;
			}
			
			return false;
		}
		
		/*virtual*/ void SpriteActionMoveTo::start(Action_Receiver *receiver)
		{
            _receiver = static_cast<Sprite*>(receiver);
            _origin = _receiver->getPosition();
			Action::start(receiver);
		}
		
		/*virtual*/ void SpriteActionMoveTo::update(const Percentage time)
		{
			Point newPosition = _origin * (1.0f - time) + _to * time;
			
			_receiver->setPosition(newPosition);
		}
		
		SpriteActionMoveTo::SpriteActionMoveTo() : Action(),
		_origin(0.0f, 0.0f),
		_to(0.0f, 0.0f),
		_receiver(nullptr)
		{
			
		}
		
	}
}




