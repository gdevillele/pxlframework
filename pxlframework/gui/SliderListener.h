//
//  SliderListener.h
//  pxlframework
//
//  Created by Adrien Duermaël on 1/4/14.
//
//


#ifndef __pxlframework__SliderListener__
#define __pxlframework__SliderListener__


namespace px
{
	namespace engine
	{
		class SliderListener
		{
		public:
			
			/**
			 * Destructor
			 */
			virtual ~SliderListener()
			{}
			
			
			/**
			 *
			 */
			virtual void onPercentageChanged( float percentage ) = 0;
			virtual void onDone( float percentage ) = 0;
			
		protected:
			
			/**
			 * Constructor
			 */
			SliderListener()
			{}
			
		private:
			
			
		};
	}
}


#endif




