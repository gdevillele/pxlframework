//
//  Action_Receiver.cpp
//  pxlframework
//
//  Created by Axel Guilmin on 29/08/13.
//
//


#include "Action_Receiver.h"

// C++
#include <algorithm>
// pxlframework
#include "utils.h"


namespace px
{
	namespace engine
	{
		Action_Receiver::Action_Receiver()
		{
		}
		
		/*virtual*/ Action_Receiver::~Action_Receiver()
		{
			for(Action *action : _actions)
			{
				delete action;
			}
			
			_actions.clear();
		}
		
		void Action_Receiver::tick(const Tick::Duration dt)
		{
			std::vector<Action*>::iterator it = _actions.begin();
			while(it != _actions.end())
			{
				Action* action = (*it);
				
				action->step(dt);
				
				if (action->isDone())
				{
					// we don't need to finish it, if it's done :p
					delete action;
					it = _actions.erase(it);
				}
				else
				{
					it++;
				}
			}
		}
		
		Action::ActionUID Action_Receiver::runAction(Action* action)
		{
			// Action creation fail management
			if (! action)
			{
                PXL_ASSERT(false);
				return Action::kNoAction;
			}
			
			action->start(this);
			_actions.push_back(action);
			
			return action->getUID();
		}
		
		void Action_Receiver::pauseAllActions()
		{
			for(Action* action : _actions)
			{
				action->pause();
			}
		}
		
		void Action_Receiver::resumeAllActions()
		{
			for(Action* action : _actions)
			{
				action->resume();
			}
		}
		
		void Action_Receiver::finishAllActions()
		{
			for(Action* action : _actions)
			{
				action->finish();
				delete action;
			}
			
			_actions.clear();
		}
		
		
		void Action_Receiver::deleteAllActions()
		{
			for(Action* action : _actions)
			{
				// We don't even finish the actions, just delete them, callbacks won't be called for callback actions
				delete action;
			}
			
			_actions.clear();
		}
		
		template <class ActionType>
		void Action_Receiver::finishActions()
		{
			std::vector<Action*>::iterator it = _actions.begin();
			while(it != _actions.end())
			{
				// dynamic_cast return nullptr if it not the right type
				ActionType *action = dynamic_cast<ActionType*>(*it);
				
				if(action != nullptr)
				{
					action->finish();
					delete action;
					it = _actions.erase(it);
				}
				else
				{
					++it;
				}
			}
		}
		
		
		void Action_Receiver::finishAction(const Action::ActionUID uid)
		{
			std::vector<Action*>::iterator it = std::find_if(_actions.begin(), _actions.end(),
															 [&uid](const Action* a)
															 {return a->getUID() == uid;});
			
			if(it != _actions.end())
			{
				(*it)->finish();
				delete *it;
				_actions.erase(it);
			}
		}
		
		void Action_Receiver::deleteAction(const Action::ActionUID uid)
		{
			std::vector<Action*>::iterator it = std::find_if(_actions.begin(), _actions.end(),
															 [&uid](const Action* a)
															 {return a->getUID() == uid;});
			
			if(it != _actions.end())
			{
				delete *it;
				_actions.erase(it);
			}
		}
		
		void Action_Receiver::resetAction(const Action::ActionUID uid)
		{
			std::vector<Action*>::iterator it = std::find_if(_actions.begin(), _actions.end(),
															 [&uid](const Action* a)
															 {return a->getUID() == uid;});
			
			if(it != _actions.end())
			{
				(*it)->reset();
			}
		}
		
		void Action_Receiver::resetAction(const Action::ActionUID uid, const Tick::Duration duration)
		{
			std::vector<Action*>::iterator it = std::find_if(_actions.begin(), _actions.end(),
															 [&uid](const Action* a)
															 {return a->getUID() == uid;});
			
			if(it != _actions.end())
			{
				(*it)->reset();
				(*it)->setDuration(duration);
			}
		}
		
		size_t Action_Receiver::countActions()
		{
			return _actions.size();
		}
		
		bool Action_Receiver::findActionByUID(const Action::ActionUID uid)
		{
			std::vector<Action*>::iterator it = _actions.begin();
			
			while(it != _actions.end())
			{
				if((*it)->getUID() == uid)
				{
					return true;
				}
				else
				{
					++it;
				}
			}
			
			return false;
		}
	}
}




