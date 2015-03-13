//
//  Toggle.h
//  pxlframework
//
//  Created by Axel Guilmin on 3/5/14.
//
//


#ifndef __pxlframework__Toggle__
#define __pxlframework__Toggle__


// pxlframework
#include "Size.h"
#include "Button.h"
// px::tools
#include "TouchListener.h"


namespace px
{
	namespace engine
	{
		/**
		 *
		 */
		class Toggle : public Button
		{
		public:
			
			/**
			 * no reference position
			 * it will be positionned relative to screen if it has no parent
			 * and relative to its parent if it has one
			 */
			
			static Toggle* newToggleWithTexture(const std::string& texture_name,
												const MenuSprite::RelativePosition relativePosition,
												const MenuSprite::RelativePosition anchor,
												const Point& position,
												bool on,
												FunctionPointerHandler* target,
												px::FunctionPointerButtonCallback selector,
												const std::string& labelOn,
												const std::string& labelOff,
                                                const std::string& font,
                                                const float fontSize,
                                                bool isBitmap);
			
			/**
			 * Destructor
			 */
			virtual ~Toggle();
			
			
#pragma mark - Public Methods -
			
			/**
			 * called by the parent
			 * inherited from MenuSprite
			 */
			virtual bool onTouch( TouchEvent event );
			
#pragma mark - Accessors -
			
			inline bool isOn() const { return _on; }
			
			inline bool isOff() const { return !_on; }
			
			
#pragma mark - Inherited -
			
			/**
			 * this method do nothing
			 * we override the Sprite::addChild method
			 * to avoid children being added to a Toggle
			 * @see addLabel and addIcon (later)
			 */
			virtual void addChild( Sprite* child );
			
			
		protected:
			
			/**
			 * Default Constructor
			 */
			Toggle();
			
		private:
			
			std::string _labelOn;
			std::string _labelOff;
			
			inline void setOn()
			{
				_on = true;
				setCurrentFrame(1);
				setLabelText(_labelOn);
			}
			
			inline void setOff()
			{
				_on = false;
				setCurrentFrame(0);
				setLabelText(_labelOff);
			}
			
			
			/** Is the toggl on on position */
			bool _on;
			
			/** Disable copying */
			DISALLOW_COPY_AND_ASSIGN(Toggle);
		};
	}
}


#endif




