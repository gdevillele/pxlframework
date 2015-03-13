//
//  Slider.h
//  pxlframework
//
//  Created by Gaëtan de Villèle on 11/22/13.
//
//


#ifndef __pxlframework__Slider__
#define __pxlframework__Slider__


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
		 * a slider button widget to be used with Menu class
		 * at the moment, it's only an horizontal slider
		 *
		 * technically, it's a MenuSprite containing another MenuSprite
		 */
		
		class SliderListener;
		
		
		class Slider : public MenuSprite
		{
		public:
			static float guiSliderTouchMargin;
            
            
			/**
			 *
			 */
			enum class Orientation
			{
				HORIZONTAL = 1,
				VERTICAL = 2
			};
			
			/**
			 * instance building function
			 */
			static Slider* newSlider(const std::string& backgroundTextureName,
									 const std::string& buttonTextureName,
									 const RelativePosition relativePosition,
									 const RelativePosition anchor,
									 const Point& position,
									 const float sliderPercentage,
									 const float sliderWidth);
			
			static Slider* newVerticalSlider(const std::string& backgroundTextureName,
											 const std::string& buttonTextureName,
											 const RelativePosition relativePosition,
											 const RelativePosition anchor,
											 const Point& position,
											 const float sliderPercentage,
											 const float sliderHeight);
			
			/**
			 * Destructor
			 */
			virtual ~Slider();
			
			
			/**
			 *
			 */
			void setListener(SliderListener* listener);
			
			/**
			 *
			 */
			void unsetListener();
			
			
#pragma mark - Methods -
			
			/**
			 * callback of the TouchListener interface
			 * it's called by the Menu
			 * @see Menu
			 */
			virtual bool onTouch( TouchEvent event );
			
			
#pragma mark - Accessors -
			
			const float getPercentage() {return _percentage;}
			
			
#pragma mark - Modifiers -
			
			
			
		protected:
			
			/**
			 * Default Constructor
			 */
			Slider();
			
			
		private:
			
			// slider button stuff
			void createSliderButton(const std::string& buttonTextureName,
									const float percentage);
			void setPercentage(const float percentage);
			
			/**
			 * orientation of the Slider
			 */
			Orientation _orientation;
			
			/**
			 * slider button
			 */
			MenuSprite* _button;
			
			/**
			 * used to move the slider button
			 */
			Point _downEventPosition;
			float _downEventPercentage;
			
			/**
			 *
			 * between 0.0f and 1.0f
			 */
			float _percentage;
			
			
			SliderListener* _listener;
			
			
			/** Disable copying */
			DISALLOW_COPY_AND_ASSIGN(Slider);
		};
	}
}


#endif




