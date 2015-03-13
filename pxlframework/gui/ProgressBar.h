//
//  ProgressBar.h
//  pxlframework
//
//  Created by Axel Guilmin on 1/17/14.
//
//


#ifndef __pxlframework__ProgressBar__
#define __pxlframework__ProgressBar__


// C++
#include <cinttypes>
// pxlframework
#include "MenuSprite.h"
// px::tools
#include "TouchListener.h"
#include "Rect.h"


namespace px
{
	namespace engine
	{
		/**
		 * a ProgressBar widget to be used with Menu class
		 * at the moment, it's only an horizontal ProgressBar
		 *
		 * It's a menusprite displaying the backgroung
		 * It contain 2 other menuSprite to display the bar
		 */
		
		class ProgressBar : public MenuSprite
		{
		public:
			
			/**
			 * Factory method
			 */
			static ProgressBar* newProgressBar(const std::string& backgroundTextureName,
											   const std::string& leftTextureName,
											   const std::string& rightTextureName,
											   const RelativePosition relativePosition,
											   const RelativePosition anchor,
											   const Point& position,
											   const float ProgressBarPercentage,
											   const float ProgressBarWidth);
			
			/**
			 * Destructor
			 */
			virtual ~ProgressBar();
			
			
#pragma mark - Methods -
			
			/**
			 * callback of the TouchListener interface
			 * it's called by the Menu
			 * @see Menu
			 */
			// virtual bool onTouch( TouchEvent event );
			
			
#pragma mark - Accessors -
			
			/**
			 * @return 0.0f to 1.0f
			 */
			const float getPercentage()
			{return _percentage;}
			
#pragma mark - Modifiers -
			
			/**
			 * @param percentage 0.0f to 1.0f
			 */
			void setPercentage(float percentage);
			
		protected:
			
			/**
			 * Default Constructor
			 */
			ProgressBar();
			
			/**
			 * ProgressBar initialisation
			 */
			bool init(const std::string& backgroundTextureName,
					  const std::string& leftTextureName,
					  const std::string& rightTextureName,
					  const RelativePosition relativePosition,
					  const RelativePosition anchor,
					  const Point& position,
					  const float ProgressBarPercentage,
					  const float ProgressBarWidth);
			
			/**
			 * between 0.0f and 1.0f
			 */
			float _percentage;
			
		private:
			
			/**
			 * Left part of the bar
			 */
			MenuSprite* _left;
			
			/**
			 * Right part of the bar
			 */
			MenuSprite* _right;
			
			/** Disable copying */
			DISALLOW_COPY_AND_ASSIGN(ProgressBar);
		};
	}
}


#endif




