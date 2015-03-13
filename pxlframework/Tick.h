//
//  Tick.h
//  pxlframework
//
//  Created by Adrien Duermaël on 8/21/13.
//
//


#ifndef __pxlframework__Tick__
#define __pxlframework__Tick__


namespace px
{
	namespace engine
	{
		class Tick
		{
		public:
			/**
			 * Type to represent a duration
			 * in seconds
			 */
			typedef float Duration;
			
			/**
			 * Type to represent a date
			 * @todo
			 */
			// typedef struct Timestamp;
			
			
			/**
			 *
			 */
			virtual void tick(const Tick::Duration dt) = 0;
		};
	}
}


#endif




