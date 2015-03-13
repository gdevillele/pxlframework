//
//  ScrollViewActionScrollTo.cpp
//  pxlframework
//
//  Created by Axel Guilmin on 4/29/14.
//
//


#include "ScrollViewActionScrollTo.h"

// pxlframework
#include "ScrollView.h"


namespace px 
{
	namespace engine
	{
		
		/*static*/ ScrollViewActionScrollTo* ScrollViewActionScrollTo::withDuration(const Tick::Duration duration, const float to)
		{
			ScrollViewActionScrollTo* action = new ScrollViewActionScrollTo();
			
			if( ! action->init(duration, to))
			{
				delete action;
				action = nullptr;
			}
			
			return action;
		}
		
		/*virtual*/ ScrollViewActionScrollTo::~ScrollViewActionScrollTo()
		{
		}
		
		bool ScrollViewActionScrollTo::init(const Tick::Duration duration, const float to)
		{
			if(Action::init(duration))
			{
				_to = to;
				return true;
			}
			
			return false;
		}
		
		/*virtual*/ void ScrollViewActionScrollTo::start(Action_Receiver *receiver)
		{
			Action::start(receiver);
			_receiver = static_cast<ScrollView*>(receiver);
			// @todo scrollview may be NULL
			_origin = _receiver->getProgress();
            
            // Manage instantaneous action case
            if(_duration <= 0.0f)
            {
                _receiver->setProgress(_to);
            }
		}
		
		/*virtual*/ void ScrollViewActionScrollTo::update(const Percentage time)
		{
			float newPosition = _origin * (1.0f - time) + _to * time;
			
            /// @todo will refresh all chidren position (again)
			_receiver->setProgress(newPosition);
		}
		
		ScrollViewActionScrollTo::ScrollViewActionScrollTo() : Action(),
		_origin(0.0f),
		_to(0.0f),
		_receiver(nullptr)
		{
			
		}
	}
}




