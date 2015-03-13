//
//  ActionRepeatForever.h
//  pxlframework
//
//  Created by Axel Guilmin on 03/09/13.
//
//


#ifndef __pxlframework__ActionRepeatForever__
#define __pxlframework__ActionRepeatForever__


// pxlframework
#include "Action.h"


namespace px
{
	namespace engine
	{
		
		/**
		 * Action Modifier : Repeat an action forever
		 * Can be used on evey kind of action
		 * @author Axel Guilmin
		 */
		class ActionRepeatForever : public Action
		{
		public:
			/**
			 * Factory method
			 * @param repeatedAction the action to repeat
			 */
			static ActionRepeatForever* withAction(Action* repeatedAction);
			
			/**
			 * Destructor
			 * Will destroy the repeated action before
			 * @todo stop the action properly
			 */
			virtual ~ActionRepeatForever();
			
			/**
			 * Initialisation used by the factory method
			 * @param duration in second
			 * @param repeatedAction the action to repeat
			 * @return false if initialisation failed
			 */
			bool init(const Tick::Duration duration, Action* repeatedAction);
			
			/**
			 * Start the rotation on the specified receiver
			 * @param receiver the WorldElement which receive the action
			 */
			virtual void start(Action_Receiver *receiver);
			
			/**
			 * called once per frame. time a value between 0 and 1
			 * For example:
			 * - 0 means that the action just started
			 * - 0.5 means that the action is in the middle
			 * - 1 means that the action is over
			 */
			virtual void update(const Percentage percentage);
			
			
			/**
			 * Finishes the inner action
			 */
			virtual void finish() {_repeatedAction->finish();}
			
			/**
			 * Action is repeating forever and never end, so it return always false
			 */
			virtual bool isDone();
			
		protected:
			/**
			 * Default Constructor
			 */
			ActionRepeatForever();
			
		private:
			/** The action to repeat */
			Action* _repeatedAction;
			
			/** Disable copying */
			DISALLOW_COPY_AND_ASSIGN(ActionRepeatForever);
		};
	}
}

#endif




