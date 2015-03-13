//
//  Action.h
//  pxlframework
//
//  Created by Axel Guilmin on 29/08/13.
//
//


#ifndef __pxlframework__Action__
#define __pxlframework__Action__


// C++
#include <cinttypes>
// pxlframework
#include "macros.h"
#include "Tick.h"


namespace px
{
	namespace engine
	{
		
		// Include loop, so we just add the prototype
		class Action_Receiver;
		
		/**
		 * Action is an interface
		 *
		 * @author Axel Guilmin
		 * @todo use a time type instead of float
		 */
		class Action
		{
			
		public:
			/**
			 * Type to manage an action UID
			 */
			typedef uint64_t ActionUID;
			
			/**
			 * Constant that mean "No Action"
			 */
			static constexpr ActionUID kNoAction = 0;
			
			/**
			 * 0.0f to 1.0f
			 */
			typedef float Percentage;
			
			/**
			 * Virtual destructor
			 */
			virtual ~Action();
			
			/**
			 * Called when the action is linked to the receiver
			 * @return bool true is the action correctly started
			 */
			virtual void start(Action_Receiver *receiver);
			
			/**
			 * Execute a step on the action, called by the tick
			 */
			void step(const Tick::Duration dt);
			
			/**
			 * Called once per frame.
			 * @param progression percentage from 0 to 1
			 * For example:
			 * - 0 means that the action just started
			 * - 0.5 means that the action is in the middle
			 * - 1 means that the action is over
			 */
			virtual void update(const Percentage progression) = 0;
			
			/**
			 * Reset action progression to 0%
			 */
			virtual inline void reset()
			{ _elapsed = 0.0f; }
			
			/**
			 * to pause the action
			 */
			inline void pause(){ _paused = true; };
			
			/**
			 * to resume the action
			 */
			inline void resume(){ _paused = false; };
			
			
			/**
			 * return true if the action has finished
			 * If isDone return true, there is big chance that the Action destructor will be called to end the action
			 */
			virtual bool isDone();
			
			/**
			 * Stops the action, without finishing it.
			 */
			//virtual void stop(){};
			
			/**
			 * Finishes the action
			 */
			virtual void finish(){update(1.0);};
			
			/**
			 * @return the duration of the action
			 */
			const Tick::Duration getDuration();
			
			/**
			 * @return the duration of the action
			 */
			inline void setDuration(const Tick::Duration duration)
			{ _duration = duration; }
			
			/**
			 * @return the UID of the action (auto-generated)
			 */
			const ActionUID getUID() const;
			
		protected:
			/**
			 * Default constructor
			 */
			Action();
			
			/**
			 * Initialisation used by the factory method
			 * @param duration in second
			 * @return false if initialisation failed
			 */
			bool init(const Tick::Duration duration);
			
			/** The receiver will be set with the 'startWithReceiver' method. */
			Action_Receiver* _receiver;
			
			/** duration in second of the action */
			Tick::Duration _duration;
			
			/** time elapsed since the action started */
			Tick::Duration _elapsed;
			
			/** indicates if action is paused or not */
			bool _paused;
			
		private:
			
			/** Auto generated unique id */
			const ActionUID _UID;
			
			/** Disable copying */
			DISALLOW_COPY_AND_ASSIGN(Action);
			
		};
	}
}


#endif




