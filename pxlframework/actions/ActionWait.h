//
//  ActionWait.h
//  pxlframework
//
//  Created by Adrien Duermaël on 12/3/13.
//
//


#ifndef __pxlframework__ActionWait__
#define __pxlframework__ActionWait__


// pxlframework
#include "Action.h"


namespace px
{
	namespace engine
	{
		/**
		 * @brief Just wait
		 * @author Axel Guilmin
		 */
		class ActionWait : public Action
		{
		public:
			
			/**
			 * Destructor
			 */
			virtual ~ActionWait()
            {/* Nothing */};
			
			/**
			 * Factory method
			 * @param selector The method to call on the Action_Receiver
			 */
			static ActionWait* withDuration(const Tick::Duration d);
			
			
			/**
			 * called once per frame. time a value between 0 and 1
			 */
			virtual void update(float progression)
            {/* Nothing */};
			
			
		protected:
			/**
			 * Default constructor
			 */
			ActionWait()
            {/* Nothing */};
			
		private:
			/** Disable copying */
			DISALLOW_COPY_AND_ASSIGN(ActionWait);
		};
		
	}
}


#endif




