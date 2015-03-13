//
//  Menu.h
//  pxlframework
//
//  Created by Adrien Duermaël on 8/21/13.
//
//


#ifndef __pxlframework__Menu__
#define __pxlframework__Menu__


// C++
#include <vector>
// px::tools
#include <GlobalListener.h>
#include <TouchListener.h>
// pxlframework
#include "FunctionPointerHandler.h"
#include "Tick.h"
#include "../actions/Action_Receiver.h"
#include "../actions/ActionCallback.h"
#include "touchPriority.h"


namespace px
{
	namespace engine
	{
		class MenuSprite;
		
		/**
		 * Menu is a virtual class
		 * a menu is like a layer
		 * it's a fullscreen container containing an array of MenuSprite objects
		 */
        class Menu : public TouchListener, public Action_Receiver, public ActionCallbackHandler, public Tick, public px::tools::GlobalListener
		{
		public:
			
			/**
			 * Default constructor
			 */
			Menu();
			
			/**
			 * Destructor
			 */
			virtual ~Menu();
			
			/**
			 * add a child in the menu
			 */
			virtual void addChild( MenuSprite* child );
			
			/**
			 * remove a child in the menu
			 */
			void removeChild( MenuSprite* child );
			
			/**
			 * returns the menu's array of children
			 */
			const std::vector<MenuSprite*>& getChildren();
			
			/**
			 * removes and destroy all children from the menu
			 */
			void removeAndDestroyAllChildren();
            
            /**
			 * removes children for renderer only (not Sprite instances)
			 */
			void stopRendering();
			
			/**
			 * register the menu to receive touch events
			 */
			void enableTouch(uint8_t priority = touchPriority::default_menu);
			
			/**
			 * unregister the menu to stop receiving touch events
			 */
			void disableTouch();
			
			/**
			 * implementation of GlobalListener interface
			 * inherited from GlobalListener
			 */
			virtual void onGlobalEvent( const std::string& eventKey ) {};
			
			/**
			 * implementation of the TouchListener interface
			 *
			 * this method dispatch touch events to the
			 * menu's buttons
			 *
			 * @return true if the touch event has been consumed
			 */
			virtual bool onTouch( TouchEvent event );
			
			/**
			 * implementation of the Tick interface
			 * inherited from Tick
			 */
			virtual void tick(const Tick::Duration dt);
            
            inline void setAlwaysConsumesTouches(bool alwaysConsumesTouches){ _alwaysConsumesTouches = alwaysConsumesTouches; };
			
			
		protected:
			bool _consumeAllTocuhes;
			
		private:
			
			
			typedef std::vector<MenuSprite*> MenuSpriteVector;
			
			/** array of children */
			MenuSpriteVector _children;
            
            /** If true, the menu will consume touches even if nothing was touched */
            bool _alwaysConsumesTouches;
			
			/** Disable copying */
			DISALLOW_COPY_AND_ASSIGN(Menu);
		};
		
	}
}


#endif




