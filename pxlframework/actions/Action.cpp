//
//  Action.cpp
//  pxlframework
//
//  Created by Axel Guilmin on 29/08/13.
//
//


#include "Action.h"

// C++
#include <algorithm>
#include <limits>
// pxlframework
#include "utils.h"


namespace px
{
	namespace engine
	{
		Action::Action() :
		_UID(reinterpret_cast<Action::ActionUID>(this)), // Auto-generated ID
		_elapsed(0.0f),
		_duration(0.0f),
		_receiver(nullptr),
		_paused(false)
		{
			// Do nothing
		}
		
		/*virtual*/ Action::~Action()
		{
			// Do nothing
		}
		
		/*virtual*/ bool Action::init(const Tick::Duration duration)
		{
            PXL_ASSERT(duration == duration);
            
			_duration = duration;

			return true;
		}
		
		/*virtual*/ void Action::start(Action_Receiver *receiver)
		{
			_receiver = receiver;
            
            if (_duration == 0)
            {
                update(1.0f);
            }
		}
		
		void Action::step(const Tick::Duration dt)
		{
			if (!_paused)
			{
				_elapsed += dt;
				update(std::min((Percentage)(_elapsed / _duration), 1.0f));
			}
		}
		
		/*virtual*/ bool Action::isDone()
		{
			return _elapsed >= _duration;
		}
		
		const Tick::Duration Action::getDuration()
		{
			return _duration;
		}
		
		const Action::ActionUID Action::getUID() const
		{
			return _UID;
		}
	}
}




