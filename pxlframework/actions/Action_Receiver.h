//
//  Action_Receiver.h
//  pxlframework
//
//  Created by Axel Guilmin on 29/08/13.
//
//


#ifndef __pxlframework__Action_Receiver__
#define __pxlframework__Action_Receiver__


// C++
#include <vector>
// pxlframework
#include "Tick.h"
#include "Action.h"


namespace px
{
	namespace engine
	{
		/**
		 * Action_Receiver is an interface for every class that need to manage actions
		 * Action_Receiver overload Tick, so you don't need to inherit from Tick
		 *
		 * @author Axel Guilmin
		 */
		class Action_Receiver : public Tick
		{
			
		public:
			
			/**
			 * inherited from Tick
			 */
			virtual void tick(const Tick::Duration dt);
			
			/**
			 * Run a given Action on this
			 */
			Action::ActionUID runAction(Action* action);
			
			
			/**
			 * Pauses every action running on this target right now
			 */
			void pauseAllActions();
			
			/**
			 * Resumes every action running on this target right now
			 */
			void resumeAllActions();
			
			/**
			 * Finishes and delete every action running on this target right now
			 */
			void finishAllActions();
			
			/**
			 * Deletes every action running on this target right now
			 */
			void deleteAllActions();
			
			/**
			 * Finish actions of the provided kind running on this target right now
			 */
			template <class ActionType>
			void finishActions();
			
			/**
			 * Finish action with ID
			 */
			void finishAction(const Action::ActionUID uid);
			
			/**
			 * Delete actions of the provided kind running on this target right now
			 */
			template <class ActionType>
			void deleteActions()
			{
				std::vector<Action*>::iterator it = _actions.begin();
				while(it != _actions.end())
				{
					// dynamic_cast return nullptr if it not the right type
					ActionType *action = dynamic_cast<ActionType*>(*it);
					
					if(action != nullptr)
					{
						delete action;
						it = _actions.erase(it);
					}
					else
					{
						++it;
					}
				}
			}
			
			/**
			 * Delete action with ID
			 */
			void deleteAction(const Action::ActionUID uid);
			
			/**
			 *
			 */
			void resetAction(const Action::ActionUID uid);
			
			/**
			 *
			 */
			void resetAction(const Action::ActionUID uid, const Tick::Duration duration);
			
			/**
			 * Return the size of the action vector, ie the number of parallel actions
			 */
			size_t countActions();
			
			/**
			 * Return true if the action with the given uid is still here
			 */
			bool findActionByUID(const Action::ActionUID uid);
			
		protected:
			/**
			 * Default Constructor
			 */
			Action_Receiver();
			
			/**
			 * Destructor
			 */
			virtual ~Action_Receiver();
			
		private:
			/** Several action can be run in parallel */
			std::vector<Action*> _actions;
			
			/** Disable copying */
			DISALLOW_COPY_AND_ASSIGN(Action_Receiver);
			
		};
	}
}


#endif




