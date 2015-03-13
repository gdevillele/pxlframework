//
//  ScrollViewActionLock.h
//  pxlframework
//
//  Created by Axel Guilmin on 4/29/14.
//
//


#ifndef __pxlframework__ScrollViewActionLock__
#define __pxlframework__ScrollViewActionLock__


// pxlframework
#include "Action.h"


namespace px
{
	namespace engine
	{
		/**
         * @file ScrollViewLock.h
		 * @brief Make the scroll view ignore touches
		 * @author Axel Guilmin
         * @since 4/29/14
		 */
		class ScrollViewActionLock : public Action
		{
		public:
			
			/**
			 * Destructor
			 */
			virtual ~ScrollViewActionLock()
            {/* Nothing */}
			
			/**
			 * Factory method
			 * @param selector The method to call on the Action_Receiver
			 */
			static ScrollViewActionLock* instantaneous();
			
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
			ScrollViewActionLock()
            {/* Nothing */}
			
		private:
            
			/** Disable copying */
			DISALLOW_COPY_AND_ASSIGN(ScrollViewActionLock);
		};
		
	}
    
}


#endif




