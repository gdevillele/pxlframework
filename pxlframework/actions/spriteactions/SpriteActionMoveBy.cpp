//
//  SpriteActionMoveBy.cpp
//  pxlframework
//
//  Created by Adrien Duermaël on 12/3/13.
//
//


// pxlframework
#include "SpriteActionMoveBy.h"


namespace px
{
	namespace engine
	{
		
		/*static*/ SpriteActionMoveBy* SpriteActionMoveBy::withDuration(const Tick::Duration duration, const Point delta)
		{
			SpriteActionMoveBy* action = new SpriteActionMoveBy();
			
			if( ! action->init(duration, delta))
			{
				delete action;
				action = nullptr;
			}
			
			return action;
		}
		
		/*virtual*/ SpriteActionMoveBy::~SpriteActionMoveBy()
		{
		}
		
		bool SpriteActionMoveBy::init(const Tick::Duration duration, const Point delta)
		{
			if(Action::init(duration))
			{
				_by = delta;
				return true;
			}
			
			return false;
		}
		
		/*virtual*/ void SpriteActionMoveBy::start(Action_Receiver *receiver)
		{
			//PXL_ASSERT( dynamic_cast<Sprite*>(receiver) != nullptr );
			
			Action::start(receiver);
			_receiver = static_cast<Sprite*>(receiver);
			// @todo sprite may be NULL
			_origin = _receiver->getPosition();
		}
		
		/*virtual*/ void SpriteActionMoveBy::update(const Percentage time)
		{
			Point newPosition = _origin + _by * time;
			
			_receiver->setPosition(newPosition);
		}
		
		SpriteActionMoveBy::SpriteActionMoveBy() : Action(),
		_origin(0.0f, 0.0f),
		_by(0.0f, 0.0f),
		_receiver(nullptr)
		{
			
		}		
	}
}




