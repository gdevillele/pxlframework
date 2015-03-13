//
//  ScrollViewActionScrollTo.h
//  pxlframework
//
//  Created by Axel Guilmin on 4/29/14.
//
//


#ifndef __pxlframework__ScrollViewActionScrollTo__
#define __pxlframework__ScrollViewActionScrollTo__


//pxlframework
#include "Action.h"


namespace px
{
	namespace engine
	{
		
        class ScrollView;
        
		class ScrollViewActionScrollTo : public Action
		{
			
		public:
			/**
			 * Factory method
			 * @param duration in second
			 * @param to
			 */
			static ScrollViewActionScrollTo* withDuration(const Tick::Duration duration, const float to);
			
			
			/**
			 * Destructor
			 */
			virtual ~ScrollViewActionScrollTo();
			
			/**
			 * Initialisation used by the factory method
			 * @param duration in second
			 * @param to
			 * @return false if initialisation failed
			 */
			bool init(const Tick::Duration duration, const float to);
			
			
			virtual void start(Action_Receiver *receiver);
			
			/**
			 * called once per frame by step() method. time a value between 0 and 1
			 * @param time percentage of the action progression
			 * For example:
			 * - 0.0 means that the action just started
			 * - 0.5 means that the action is in the middle
			 * - 1.0 means that the action is over
			 */
			virtual void update(const Percentage time);
			
			/**
			 * Called when the game is paused
			 */
			virtual void pause() {};
			
			virtual void stop() {update(1.0f);}
			
		protected:
			/**
			 * Default constructor
			 */
			ScrollViewActionScrollTo();
			
			/** Point at the begining of the action */
			float _origin;
			
			/** Where to move to */
			float _to;
			
		private:
			
			/** We know the reciever IS a scrollView, so we save a casted version in start */
			ScrollView *_receiver;
			
			/** Disable copying */
			DISALLOW_COPY_AND_ASSIGN(ScrollViewActionScrollTo);
			
		};
		
	}
}


#endif




