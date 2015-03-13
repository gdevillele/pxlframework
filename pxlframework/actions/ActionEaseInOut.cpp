//
//  ActionEaseInOut.cpp
//  pxlframework
//
//  Created by Axel Guilmin on 30/08/13.
//
//



#include "ActionEaseInOut.h"

// C++
#include <cmath>


namespace px
{
	namespace engine
	{
		/*static*/ ActionEaseInOut* ActionEaseInOut::withRatio(const float rate, Action* easedAction)
		{
			ActionEaseInOut* action = new ActionEaseInOut();
			
			if( ! action->init(rate, easedAction))
			{
				delete action;
				action = nullptr;
			}
			
			return action;
		}
		
		
		bool ActionEaseInOut::init(const float rate, Action* easedAction)
		{
			if(Action::init(easedAction->getDuration()))
			{
				_easedAction = easedAction;
				_rate = rate;
				return true;
			}
			
			return false;
		}
		
		/*virtual*/ void ActionEaseInOut::start(Action_Receiver *receiver)
		{
			_easedAction->start(receiver);
		}
		
		/*virtual*/ void ActionEaseInOut::update(float progression)
		{
			progression *= 2;
			if (progression < 1.0f)
			{
				_easedAction->update(0.5f * powf(progression, _rate));
			}
			else
			{
				_easedAction->update(1.0f - 0.5f * powf(2.0f - progression, _rate));
			}
		}
		
		
		/*virtual*/ ActionEaseInOut::~ActionEaseInOut()
		{
			if(_easedAction != nullptr)
			{
				delete _easedAction;
				_easedAction = nullptr;
			}
		}
		
		ActionEaseInOut::ActionEaseInOut() : Action(),
		_easedAction(nullptr),
		_rate(0.0f)
		{
		}
	}
}




