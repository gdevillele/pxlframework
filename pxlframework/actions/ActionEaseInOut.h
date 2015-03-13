//
//  ActionEaseInOut.h
//  pxlframework
//
//  Created by Axel Guilmin on 30/08/13.
//
//


#ifndef __pxlframework__ActionEaseInOut__
#define __pxlframework__ActionEaseInOut__


// pxlframework
#include "Action.h"


namespace px
{
	namespace engine
	{
		/**
		 * Action Modifier : Ease In and Out
		 * Will slow down the action at the begining and the end to make it smoother
		 * @author Axel Guilmin
		 */
		class ActionEaseInOut : public Action
		{
		public:
			/**
			 * Destructor
			 * Will destroy the easedAction before
			 * @todo stop the action properly
			 */
			virtual ~ActionEaseInOut();
			
			/**
			 * Factory method
			 * @param easedAction the action to alterate
			 * @param rate the higher it is, the smoother the action will be, put 2.0f for example
			 */
			static ActionEaseInOut* withRatio(const float rate, Action* easedAction);
			
			/**
			 * Initialisation used by the factory method
			 * @param rate the higher it is, the smoother the action will be, put 2.0f for example
			 * @return false if initialisation failed
			 */
			bool init(const float rate, Action* easedAction);
			
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
			virtual void update(float progression);
			
			/**
			 * Stop the inner action
			 */
			virtual void finish() {_easedAction->finish();}
			
			
		protected:
			/**
			 * Default constructor
			 */
			ActionEaseInOut();
			
		private:
			/** The action to ease */
			Action* _easedAction;
			
			/** The rate for the easing */
			float _rate;
			
			/** Disable copying */
			DISALLOW_COPY_AND_ASSIGN(ActionEaseInOut);
			
		};
	}
}


#endif




