//
//  ActionCallback.cpp
//  pxlframework
//
//  Created by Axel Guilmin on 11/7/13.
//
//


#include "ActionCallback.h"


namespace px
{
	namespace engine
	{
		/*virtual*/ ActionCallback::~ActionCallback()
		{
			
		}
		
		/*static*/ ActionCallback* ActionCallback::withTargetAndSelector(ActionCallbackHandler* target,Callback selector)
		{
			ActionCallback* action = new ActionCallback();
			
			if( ! action->init())
			{
				delete action;
				action = nullptr;
			}
			else
			{
				action->_target = target;
				action->_selector = selector;
			}
			
			return action;
		}
		
		/*static*/ ActionCallback* ActionCallback::withTargetAndSelectorWithSprite(ActionCallbackHandler* target,CallbackWithSprite selector, Sprite* parameter)
		{
			ActionCallback* action = new ActionCallback();
			
			if( ! action->init())
			{
				delete action;
				action = nullptr;
			}
			else
			{
				action->_target = target;
				action->_selectorWithSprite = selector;
				action->_parameter = parameter;
			}
			
			return action;
		}
		
		
		
		bool ActionCallback::init()
		{
			return Action::init(0.0f); // Instantaneous
		}
		
		ActionCallback::ActionCallback() : Action(),
		_target(nullptr),
		_selector(nullptr),
		_selectorWithSprite(nullptr),
		_parameter(nullptr)
		{
			
		}
		
		/*virtual*/ void ActionCallback::update(float progression)
		{
			if(_target)
			{
				if (_selector)
					(_target->*_selector)();
				else if (_selectorWithSprite)
					(_target->*_selectorWithSprite)(_parameter);
			}
		}
		
	}
}




