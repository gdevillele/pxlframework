//
//  ScrollViewActionUnlock.h
//  pxlframework
//
//  Created by Axel Guilmin on 4/29/14.
//
//


#ifndef __pxlframework__ScrollViewActionUnlock__
#define __pxlframework__ScrollViewActionUnlock__


// pxlframework
#include "Action.h"


namespace px
{
	namespace engine
	{
		/**
         * @file ScrollViewUnlock.h
		 * @brief Make the scroll view accept touches
		 * @author Axel Guilmin
         * @since 4/29/14
		 */
		class ScrollViewActionUnlock : public Action
		{
		public:
			
			/**
			 * Destructor
			 */
			virtual ~ScrollViewActionUnlock()
            {/* Nothing */}
			
			/**
			 * Factory method
			 * @param selector The method to call on the Action_Receiver
			 */
			static ScrollViewActionUnlock* instantaneous();
			
			/**
			 * Called once per frame. time a value between 0 and 1
			 */
			virtual void update(float progression)
            {/* Nothing */}
            
            /**
             *
             */
            virtual void start(Action_Receiver *receiver);
			
		protected:
            
			/**
			 * Default constructor
			 */
			ScrollViewActionUnlock()
            {/* Nothing */}
			
		private:
            
			/** Disable copying */
			DISALLOW_COPY_AND_ASSIGN(ScrollViewActionUnlock);
		};
		
	}
    
}


#endif




