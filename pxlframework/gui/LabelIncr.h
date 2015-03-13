//
//  LabelIncr.h
//  pxlframework
//
//  Created by Adrien Duermaël on 3/17/14.
//
//


#ifndef __pxlframework__LabelIncr__
#define __pxlframework__LabelIncr__


// pxlframework
#include "Label.h"


namespace px
{
	namespace engine
	{
		
		/**
		 * A LabelIncr displays integers only
		 * You can use it if you want to animate incrementation/decrementation
		 */
		class LabelIncr : public Label
		{
		public:
			
			/**
			 * add this label in a Menu / MenuSprite
			 */
			static LabelIncr* newLabelIncr(const MenuSprite::RelativePosition relativePosition,
										   const MenuSprite::RelativePosition anchor,
										   const Point& position,
										   int number,
										   const std::string& font,
										   Tick::Duration maximumTotalTime,
										   int minimumUpdateValue);
			
			/**
			 * to be used as a simple Sprite : add this label in a Sprite / WorldElement
			 */
			static LabelIncr* newLabelIncr(const Point& anchor,
										   const Point& position,
										   int number,
										   const std::string& font,
										   Tick::Duration maximumTotalTime,
										   int minimumUpdateValue);
			
			/**
			 * Destructor
			 */
			virtual ~LabelIncr();
			
			
			// ---------- ACCESSORS ----------
			
			/**
			 * Return number (integer)
			 */
			inline const int getNumber() const {return _number;}
			
			/**
			 * Return displayed number (integer)
			 */
			inline const int getNumberDisplayed() const {return _numberDisplayed;}
			
			
			// ---------- MODIFIERS ----------
			
			/**
			 * Define number
			 */
			inline void setNumber( const int number )
			{
				_number = number;
                _timeRemaining = _maximumTotalTime;
			}
            
            /**
			 * Define number, do not play animation
			 */
			inline void setNumberDisplayed( const int number )
			{
				_number = number;
                _numberDisplayed = number;
                setText(tostr(_numberDisplayed));
			}
			
			inline void setMaximumTotalTime( const Tick::Duration maximumTotalTime ){_maximumTotalTime = maximumTotalTime; _timeRemaining = _maximumTotalTime; }
			
			inline void setMinimumUpdateValue ( const int minimumUpdateValue ){ _minimumUpdateValue = minimumUpdateValue;}
			
            inline void setLoopSFX(std::string sfx) { _sfx = sfx; }
			
			
			virtual void tick(const Tick::Duration dt);
			
			
		protected:
			
			/**
			 * Default Constructor
			 */
			LabelIncr();
			
			
			
		private:
			
			/**
			 * number to display
			 */
			int _number;
			
			/**
			 * The number currently displayed
			 * _numberDisplayed == _number at the end of the animation
			 */
			int _numberDisplayed;
			
			
			/**
			 * The maximum total time to reach _numberDisplayed == _number
			 */
			Tick::Duration _maximumTotalTime;
			
			
			/**
			 * Time to reach _numberDisplayed == _number
			 */
			Tick::Duration _timeRemaining;
			
			/**
			 * The minium value to add (per tick)
			 * Maybe we should update that to get a "per second" option
			 */
			int _minimumUpdateValue;
            
            /**
             * Sound effect to play while number is changing (optional)
             */
            std::string _sfx;
			
			/**
			 * Disable copying
			 */
			DISALLOW_COPY_AND_ASSIGN(LabelIncr);
		};
	}
}


#endif




