//
//  ActionRepeatForever.cpp
//  pxlframework
//
//  Created by Axel Guilmin on 03/09/13.
//
//


#include "ActionRepeatForever.h"


namespace px
{
	namespace engine
	{
		/*static*/ ActionRepeatForever* ActionRepeatForever::withAction(Action* repeatedAction)
		{
			ActionRepeatForever* action = new ActionRepeatForever();
			
			if( ! action->init(repeatedAction->getDuration(), repeatedAction))
			{
				delete action;
				action = nullptr;
			}
			
			return action;
		}
		
		bool ActionRepeatForever::init(const Tick::Duration duration, Action* repeatedAction)
		{
			if(Action::init(duration))
			{
				_repeatedAction = repeatedAction;
				return true;
			}
			return false;
		}
		
		/*virtual*/ void ActionRepeatForever::start(Action_Receiver *receiver)
		{
			Action::start(receiver);
			_repeatedAction->start(receiver);
		}
		
		/*virtual*/ void ActionRepeatForever::update(const Percentage percentage)
		{
			if(_elapsed > _duration)
				_elapsed = 0.0f;
			
			_repeatedAction->update(percentage);
		}
		
		/*virtual*/ ActionRepeatForever::~ActionRepeatForever()
		{
			if(_repeatedAction != nullptr)
			{
				delete _repeatedAction;
				_repeatedAction = nullptr;
			}
		}
		
		/*virtual*/ bool ActionRepeatForever::isDone()
		{
			return false;
		}
		
		ActionRepeatForever::ActionRepeatForever() : Action(),
		_repeatedAction(nullptr)
		{
		}
	}
}




