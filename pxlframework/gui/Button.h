//
//  Button.h
//  pxlframework
//
//  Created by Adrien Duermaël on 8/21/13.
//
//


#ifndef __pxlframework__Button__
#define __pxlframework__Button__


// C++
#include <string>
#include <vector>
// pxlframework
#include "ActionCallback.h"
#include "FunctionPointerHandler.h"
#include "Size.h"
#include "Sprite.h"
#include "MenuSprite.h"
#include "Label.h"
// pxltools
#include "TouchListener.h"


namespace px
{
	namespace engine
	{
		/**
		 * @todo we could override addChild and use instead addIcon and addLabel
		 */
		class Button : public MenuSprite, public px::FunctionPointerHandler, public ActionCallbackHandler
		{
		public:
            static float guiButtonTouchMargin;
            static float buttonBreathingSize;
            static float buttonIncreaseSizeWhenTouched;
        
			/**
			 * no reference position
			 * it will be positionned relative to screen if it has no parent
			 * and relative to its parent if it has one
			 */
			static Button* newButton(const std::string& textureName,
									 const MenuSprite::RelativePosition relativePosition,
									 const MenuSprite::RelativePosition anchor,
									 const Point& position,
									 FunctionPointerHandler* target,
									 px::FunctionPointerButtonCallback selector);
			
			/**
			 * Convert a MenuSprite in a button
			 */
			static Button* newButton(MenuSprite *content,
									 FunctionPointerHandler* target,
									 px::FunctionPointerButtonCallback selector);
			
			/**
			 * Destructor
			 */
			virtual ~Button();
			
			
			virtual void setContentSize(const Size size);
			
			
#pragma mark - Public Methods -
			
			/**
			 * callback that should be called if the Button has a custom function callback defined
			 * to call this custom callback function
			 */
			void clickCallback();
            
            /**
             * In case we set a target & selector for touch down event
             */
            void touchDownCallback();
            
            /**
             * In case we set a target & selector for touch up event (even outside)
             */
            void touchUpCallback();
			
			/**
			 * callback that should be called if the button doesn't have any callback defined
			 */
			void defaultCallback();
			
			/**
			 * called by the parent
			 * inherited from MenuSprite
			 */
			virtual bool onTouch( TouchEvent event );
			
			
			
#pragma mark - Accessors -
			
			/**
			 * return the text of the button's label
			 * return an empty string if the button
			 * hasn't a label
			 */
			const std::string getText() const;
			inline const bool getImportant() const {return _important;}
			inline void* getUserData() const {return _userData;}
            inline int getUserDataInt() const {return _userDataInt;}
            inline const std::string& getUserDataString() const {return _userDataString;}
			
			
			
#pragma mark - Modifiers -
			
			void setImportant(bool important);
			
			inline void setUserData(void* userData) {_userData = userData;}
            inline void setUserDataInt(int userDataInt) {_userDataInt = userDataInt;}
            inline void setUserDataString(const std::string& userDataString) {_userDataString = userDataString;}
			
			/**
			 *
			 */
			void addLabel(const std::string& text, const Color color, const std::string& font,const float fontSize,bool isBitmap);
			
			/**
			 *
			 */
			void setLabelText(const std::string& text);
			
			/**
			 *
			 */
			void setLabelColor(const Color color);
			
			/**
			 * define the target of the click callback
			 */
			void setTarget(FunctionPointerHandler* target);
			
			/**
			 * define the target's method of the click callback
			 */
			void setSelector(px::FunctionPointerButtonCallback selector);
            
            
            void setTouchDownTargetAndSelector(FunctionPointerHandler* target, px::FunctionPointerButtonCallback selector);
            void setTouchUpTargetAndSelector(FunctionPointerHandler* target, px::FunctionPointerButtonCallback selector);
			
			/*
			 * Disable the button
			 */
			void disable();
			
			/**
			 * Enable the button (It's already enabled by default)
			 */
			void enable();
			
			
#pragma mark - Inherited -
			
			
		protected:
			/**
			 * Default Constructor
			 */
			Button();
			
			/**
			 * switch button to pressed state
			 */
			void press();
			
			/**
			 * switch button to released state (idle/normal)
			 */
			void release();
			
			/** target of the button's callback */
			FunctionPointerHandler* _target;
			
			/** function of the button's callback */
			px::FunctionPointerButtonCallback _selector;
            
            
            /** Target for some cases where need to know when the button is being touched down*/
            FunctionPointerHandler* _target_touch_down;
            
            /** Callback for some cases where we need to know when the button is being touched down */
            px::FunctionPointerButtonCallback _selector_touch_down;
            
            
            /** Target for some cases where need to know when the button is being touched up (even outside)*/
            FunctionPointerHandler* _target_touch_up;
            
            /** Callback for some cases where we need to know when the button is being touched up (even outside*/
            px::FunctionPointerButtonCallback _selector_touch_up;
            
            
			
			/** user data */
			void* _userData;
            int _userDataInt;
            std::string _userDataString;
			
			/** text displayed on top of the button */
			px::engine::Label* _label;
			
		private:
			/**
			 *
			 */
			void animateBreathing();
			
			/**
			 *
			 */
			virtual void animatePressed();
			
			/**
			 *
			 */
			virtual void animateReleased();
			
			
			/** indicate whether the button is flagged as important or not */
			bool _important;
			
			/** A disabled button do nothing when pressed */
			bool _enabled;
			
			/** Disable copying */
			DISALLOW_COPY_AND_ASSIGN(Button);
		};
	}
}


#endif




