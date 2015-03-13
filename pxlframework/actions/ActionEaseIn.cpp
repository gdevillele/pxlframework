//
//  ActionEaseIn.cpp
//  pxlframework
//
//  Created by Axel Guilmin on 4/30/14.
//
//


// C++
#include <cmath>
// pxlframework
#include "ActionEaseIn.h"


namespace px
{
	namespace engine
	{
		/*static*/ ActionEaseIn* ActionEaseIn::withRatio(const float rate, Action* easedAction)
		{
			ActionEaseIn* action = new ActionEaseIn();
			
			if( ! action->init(rate, easedAction))
			{
				delete action;
				action = nullptr;
			}
			
			return action;
		}
		
		bool ActionEaseIn::init(const float rate, Action* easedAction)
		{
			if(Action::init(easedAction->getDuration()))
			{
				_easedAction = easedAction;
				_rate = rate;
				return true;
			}
			
			return false;
		}
		
		/*virtual*/ void ActionEaseIn::start(Action_Receiver *receiver)
		{
			_easedAction->start(receiver);
		}
		
		/*virtual*/ void ActionEaseIn::update(float progression)
		{
            _easedAction->update(powf(progression, _rate));
		}
		
		
		/*virtual*/ ActionEaseIn::~ActionEaseIn()
		{
			if(_easedAction != nullptr)
			{
				delete _easedAction;
				_easedAction = nullptr;
			}
		}
		
		ActionEaseIn::ActionEaseIn() : Action(),
		_easedAction(nullptr),
		_rate(0.0f)
		{
		}
	}
}




