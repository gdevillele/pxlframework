//
//  ActionSequence.cpp
//  pxlframework
//
//  Created by Axel Guilmin on 10/16/13.
//
//


#include "ActionSequence.h"

// pxlframework
#include "utils.h"


namespace px
{
	namespace engine
	{
		/*virtual*/ ActionSequence::~ActionSequence()
		{
			if(_actions[0] != nullptr)
			{
				delete _actions[0];
				_actions[0] = nullptr;
			}
			if(_actions[1] != nullptr)
			{
				delete _actions[1];
				_actions[1]  = nullptr;
			}
		}
		
		bool ActionSequence::init(size_t size, Action** actions)
		{
			if(size < 2)
			{
				// Bad use of the sequence
				PXLLOG("!!! ActionSequence ERROR !!! Do not create a sequence with less than 2 actions you fool !");
				return false;
			}
			else if(size < 3)
			{
				return init(actions[0], actions[1]);
			}
			else
			{
				// Create a sequence with every action but the last
				ActionSequence* sequence = new ActionSequence();
				
				if( ! sequence->init(size-1, actions))
				{
					delete sequence;
					sequence = nullptr;
				}
				
				// The sequence created will be played first, then the last action
				return init(sequence, actions[size-1]);
			}
		}
		
		bool ActionSequence::init(Action *action1, Action *action2)
		{
			if( action1 != nullptr && action2 != nullptr &&
			   Action::init(action1->getDuration() + action2->getDuration()) )
			{
				_actions[0] = action1;
				_actions[1] = action2;
				return true;
			}
			return false;
		}
		
		/*virtual*/ void ActionSequence::start(Action_Receiver *receiver)
		{
			_receiver = receiver;
			_current = -1;
			
			
			/**
			 * Hack (by Ad)
			 * Hey Axel, I start here all the actions, setting receivers, just to avoid a crash
			 * Because if you stop an ActionSequence, _receivers are not set for all actions inside
			 * And so it crashes when stopping them (because it call update(1.0), using the receiver (nullptr)
			 *
			 * We have to find a better way around that issue.
			 **/
			_actions[0]->start(_receiver);
			_actions[1]->start(_receiver);
		}
		
		/*virtual*/ void ActionSequence::update(const Percentage t)
		{
			int found = 0;
			float new_t = 0.0f;
			float split = _actions[0]->getDuration() / getDuration();
			
			if( t < split ) // action[0]
			{
				found = 0;
				new_t = split != 0 ? t / split : 1;
			}
			else // action[1]
			{
				found = 1;
				new_t = split != 1 ? (t - split) / (1 - split ) : 1;
			}
			
			if( found != _current ) // Current changed
			{
				if (_current == 0) // finish the first action before starting the second one
				{
					_actions[_current]->finish();
				}
				
				_actions[found]->start(_receiver);
			}
			
			_current = found;
			_actions[_current]->update(new_t);
		}
		
		ActionSequence::ActionSequence() :
		_actions{nullptr, nullptr},
		_current(-1)
		{
			// Do nothing
		}
		
		/*virtual*/ void ActionSequence::finish()
		{
			if( _actions[0] != nullptr)
				_actions[0]->finish();
			
			if( _actions[1] != nullptr)
				_actions[1]->finish();
		}
	}
}




