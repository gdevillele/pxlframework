//
//  ActionSequence.h
//  pxlframework
//
//  Created by Axel Guilmin on 10/16/13.
//
//


#ifndef __pxlframework__ActionSequence__
#define __pxlframework__ActionSequence__


// C++
#include <cstddef>
#include <math.h>
// pxlframework
#include "Action.h"


namespace px
{
	namespace engine
	{
		/**
		 * Action Modifier : Sequence
		 * Chain severeal actions, all action should have the same reciever
		 * @detail it is a chain, one sequence contain one "final" and action and another sequence. The "last" sequence contain 2 "final" actions
		 * @author Axel Guilmin
		 */
		class ActionSequence : public Action
		{
		public:
			/**
			 * Factory method
			 * @param actions list of Actions separated by a comma, at least two actions
			 */
			// Templated method cannot be implemented in cpp :S
			template <class ...T> static ActionSequence* withActions(T... actions)
			{
				ActionSequence* sequence = new ActionSequence();
				
				Action* actionsArray[sizeof...(actions)] = {static_cast<Action*>(actions)...};
				
				if( ! sequence->init(sizeof...(actions), actionsArray))
				{
					delete sequence;
					sequence = nullptr;
				}
				
				return sequence;
			}
            
            /**
             * @param actionArray a C-array of action
             * @param size the size of actionArray
             */
            static ActionSequence* withActionsArray(Action **actionsArray, size_t size)
			{
				ActionSequence* sequence = new ActionSequence();
				
				if( ! sequence->init(size, actionsArray))
				{
					delete sequence;
					sequence = nullptr;
				}
				
				return sequence;
			}
			
			
			/**
			 * Destructor
			 * Will destroy the inner actions before
			 */
			virtual ~ActionSequence();
			
			/**
			 * Initialisation used by the factory method
			 * @param size size of the array "actions"
			 * @param action array of Actions pointer to concatenate
			 * @return false if initialisation failed
			 */
			bool init(size_t size, Action** actions);
			
			/**
			 * Initialisation used by the factory method
			 * @param action1 first action
			 * @param action2 second action
			 * @return false if initialisation failed
			 */
			bool init(Action *action1, Action* action2);
			
			/**
			 * Start the rotation on the specified receiver
			 * @param receiver the Action_Receiver which receive the action
			 */
			virtual void start(Action_Receiver *receiver);
			
			/**
			 * Will update one inner action
			 */
			virtual void update(const Percentage t);
			
			/**
			 * Stop both actions
			 */
			virtual void finish();
			
			
		protected:
			/**
			 * Default Constructor
			 */
			ActionSequence();
			
		private:
			/** The actions to chain */
			Action* _actions[2];
			
			/** Index of the runnig action
			 */
			int8_t _current;
			
			/** Disable copying */
			DISALLOW_COPY_AND_ASSIGN(ActionSequence);
		};
	}
}


#endif




