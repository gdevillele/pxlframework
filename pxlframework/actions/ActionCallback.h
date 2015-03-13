//
//  ActionCallback.h
//  pxlframework
//
//  Created by Axel Guilmin on 11/7/13.
//
//


#ifndef __pxlframework__ActionCallback__
#define __pxlframework__ActionCallback__


// pxlframework
#include "Action.h"
#include "Sprite.h"


namespace px
{
	namespace engine
	{
		class ActionCallbackHandler{};
		
		typedef void (ActionCallbackHandler::*Callback)();
		typedef void (ActionCallbackHandler::*CallbackWithSprite)(Sprite* param);
	};
	
#define ActionCallbackHandler_selector(_SELECTOR) (px::engine::Callback)(&_SELECTOR)
#define ActionCallbackHandlerWithSprite_selector(_SELECTOR) (px::engine::CallbackWithSprite)(&_SELECTOR)
	
	
	namespace engine
	{
		
		/**
		 * @brief Call a callback on the receiver, then end
		 * @author Axel Guilmin
		 * @todo add a duration
		 */
		class ActionCallback : public Action
		{
		public:
			
			/**
			 * Destructor
			 */
			virtual ~ActionCallback();
			
			/**
			 * Factory method
			 * @param selector The method to call on the Action_Receiver
			 */
			static ActionCallback* withTargetAndSelector(ActionCallbackHandler* target, Callback selector);
			
			/**
			 * Factory method
			 * @param selector The method to call on the Action_Receiver
			 * @param parameter A pointer that can be used by the callback method
			 */
			static ActionCallback* withTargetAndSelectorWithSprite(ActionCallbackHandler* target, CallbackWithSprite selector, Sprite* parameter);
			
			/**
			 * Initialisation used by the factory method
			 * @return false if initialisation failed
			 */
			bool init();
			
			/**
			 * called once per frame. time a value between 0 and 1
			 */
			virtual void update(float progression);
			
			
			/**
			 * Do nothing
			 */
			virtual void stop(){};
			
			
		protected:
			/**
			 * Default constructor
			 */
			ActionCallback();
			
			
		private:
			/** The method to call */
			ActionCallbackHandler* _target;
			
			Callback _selector;
			
			/// @todo create a new action for the action with sprite
			CallbackWithSprite _selectorWithSprite;
			
			/* A parameter, nullptr by default */
			Sprite* _parameter;
			
			/** Disable copying */
			DISALLOW_COPY_AND_ASSIGN(ActionCallback);
		};
		
	}
}


#endif




