//
//  Menu.cpp
//  pxlframework
//
//  Created by Adrien Duermaël on 8/21/13.
//
//


#include "Menu.h"

// C++
#include <cassert>
#include <algorithm>
// pxlframework
#include "MenuSprite.h"
#include "ScaleUtils.h"
#include "Button.h"
#include "Slider.h"
// px::tools
#include <TouchNotifier.h>


namespace px
{
	namespace engine
	{
		
#pragma mark - Constructor / Destructor -
		
		Menu::Menu() :
		_children(),
        _alwaysConsumesTouches(false)
		{
			enableTouch();
		}
		
		
		
		/*virtual*/
		Menu::~Menu()
		{
			disableTouch();
			
			// destroy all menu children and remove theirs
			// pointers from the children's array
			for(MenuSprite* child : _children)
			{
				delete child;
			}
			_children.clear();
		}
		
		
		
#pragma mark - Public Methods -
		
		void Menu::addChild(MenuSprite* child)
		{
			PXL_ASSERT( child != nullptr );
			
			_children.push_back(child);
		}
		
		void Menu::removeChild( MenuSprite* child )
		{
			PXL_ASSERT( child != nullptr );
			
			MenuSpriteVector::iterator it = std::find(_children.begin(), _children.end(), child);
			
			if (it != _children.end())
			{
				_children.erase(it);
				delete child;
			}
		}
		
		
		
		const std::vector<MenuSprite*>& Menu::getChildren()
		{
			return _children;
		}
		
		void Menu::removeAndDestroyAllChildren()
		{
			// destroy all menu children and remove theirs
			// pointers from the children's array
			for(MenuSprite* child : _children)
			{
				delete child;
			}
			_children.clear();
		}
        
        void Menu::stopRendering()
        {
            for(MenuSprite* child : _children)
			{
                child->stopRendering();
			}
        }
		
		void Menu::enableTouch(uint8_t priority)
		{
			// register for touch events
			TouchNotifier::sharedInstance()->registerListener(this, priority);
		}
		
		void Menu::disableTouch()
		{
			TouchNotifier::sharedInstance()->removeListener(this);
		}
		
#pragma mark - Inherited Methods -
		
		bool Menu::onTouch(TouchEvent event)
		{
			// a false result means the touch event is not consumed
			// true means it's consumed and it won't be transmitted
			// to next touch event listener
			bool result = false;
			
			// convert event position from pixel to game point units
			float scale = px::engine::utils::scaling::pixelToPoint();
			event.setX(event.getX() * scale);
			event.setY(event.getY() * scale);
			
			// then we dispatch the touch event to all children of the Menu
			for (MenuSpriteVector::const_reverse_iterator it = _children.rbegin(); it != _children.rend(); ++it)
			{
				MenuSprite* menuSprite = (*it);
				
				// transmit event to child
				result = menuSprite->onTouch(event);
				// if event has been consumed by the child we stop to dispatch it
				if( result == true )
				{
					break;
				}
			}
			
			return (_alwaysConsumesTouches || result);
		}
		
		
		
		void Menu::tick(const Tick::Duration dt)
		{
			for (Sprite *s : _children)
			{
				s->tick(dt);
			}
			Action_Receiver::tick(dt);
		}
	}
}




