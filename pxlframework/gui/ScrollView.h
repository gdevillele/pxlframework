//
//  ScrollView.h
//  pxlframework
//
//  Created by Gaëtan de Villèle on 12/12/13.
//
//


#ifndef __pxlframework__ScrollView__
#define __pxlframework__ScrollView__


// C++
#include <cinttypes>
// pxlframework
#include "MenuSprite.h"


namespace px
{

	namespace engine
	{
		
		/**
		 * the children of a ScrollView widget are MenuSprite widgets
		 *
		 *
		 */
		class ScrollView : public MenuSprite
		{
		public:
			
			/**
			 * possible states of a ScrollView
			 */
			enum class State : uint8_t
			{
				UNDEFINED      = 0, // NOT USED
				IDLE           = 1, // waiting to be touched
				TOUCHED_DOWN   = 2, // has received touch down but is not dragging (still within the margin)
				USERSCROLLING  = 3, // currently being scrolled by the user (with touch events)
				AUTOSCROLLING  = 4, // currently being scrolled programmatically
                DIRECTSCROLL   = 5, // Progress has been set directly (will stay only 1 tick)
			};
			
			/**
			 * possible orientations of a ScrollView
			 */
			enum class Orientation : uint8_t
			{
				UNKNOWN = 0,
				VERTICAL = 1,
				HORIZONTAL = 2,
				//VERTICALANDHORIZONTAL = 3 // maybe later
			};
			
	#pragma mark - Factory methods -
			
			static ScrollView* newScrollView(const Size contentSize,
											 const MenuSprite::RelativePosition relativePosition,
											 const MenuSprite::RelativePosition anchor,
											 const Point& position,
											 const Orientation orientation,
											 const float scrollableContentSize,
											 const float scrollMargin);
			
			
			
	#pragma mark - Destructor -
			
			/**
			 * Destructor
			 */
			virtual ~ScrollView();
			
			
			
	#pragma mark - Inherited -
			
			/**
			 * inherited method from Sprite
			 */
			virtual void tick(const Tick::Duration dt);
			
			/**
			 * inherited method from Sprite
			 * we need to redefine this method
			 * because we need to do some additional
			 * positioning stuff while adding a child
			 */
			virtual void addChild(Sprite* child);
			
			/**
			 * called by the parent
			 * inherited from MenuSprite
			 */
			virtual bool onTouch( TouchEvent event );
			
			
			
	#pragma mark - Accessors -
			
			const State getState() const {return _state;}
			const Orientation getOrientation() const {return _orientation;}
			const Point& getTouchDownPosition() const {return _touchDownPosition;}
			const Size getScrollableContentSize() const {return _scrollableContentSize;}
			const float getScrollSpeed() const {return _scrollSpeed;}
			const float getProgress() const {return _progress;}
            bool hasInertia() const {return _inertia;}
            bool doesIgnoreTouches() const {return _ignoreTouches;}
			const float getScrollMargin() const {return _scrollMargin;}
			
			
	#pragma mark - Modifiers -
			
			void setState(State state) {_state = state;}
			void setOrientation(Orientation orientation);
			void setTouchDownPosition(const Point& position) {_touchDownPosition.set2D(position.getX2D(), position.getY2D());}
			void setScrollableContentSize(const Size size) {_scrollableContentSize = size;}
			void setScrollSpeed(const float speed) {_scrollSpeed = speed;}
			void setScrollMargin(const float margin) {_scrollMargin = margin;}
			/**
			 * define the progression of the scrollview programmatically
			 */
			void autoscrollTo(float progress);
            /**
             * /!\ Need one tick to take effect
             */
            void setProgress(float progress);
            /**
             * Ignore the touch, the scrollView will only move promagatically
             */
			void ignoreTouches()
            { _ignoreTouches = true; }
            /**
             * Accept touches (default behaviour)
             */
            void acceptTouches()
            { _ignoreTouches = false; }
			
			
		protected:
			
			/**
			 * Default constructor
			 */
			ScrollView();
			
			
			bool init(const Size contentSize,
					  const MenuSprite::RelativePosition relativePosition,
					  const MenuSprite::RelativePosition anchor,
					  const Point& position,
					  const Orientation orientation,
					  const float scrollableContentSize,
					  const float scrollMargin);
			
			
		private:
			
			/**
			 * this method updates the children positions
			 * using the current values of _progress and _previousProgress attributes
			 * it's called by scrollview tick
			 */
			void refreshChildrenPosition(const Tick::Duration dt);
			
			//		void addToProgress(const float delta);
			
			// std::vector<MenuSprite*> overallChildren;
			// uint32_t shownChildrenMinLimit (first children shown) // not really doable
			// uint32_t shownChildrenMaxLimit (last children shown) // not really doable
			// uint32_t shownMinLimitInPoints;
			// uint32_t shownMaxLimitInPoints;
			
			
			/**
			 * current state of the scrollview
			 */
			State _state;
			
			/**
			 * Orientation of the scroll view
			 */
			Orientation _orientation;
			
			/**
			 * scroll current progress value (in points, 0.0f == left of the scrollView is on the left of the screen)
			 */
			float _progress;
	        
	        /**
	         * For auto scroll
	         */
	        float _progressToGo = 0.0f;
	        
	        /**
	         * Where the auto scroll started
	         */
	        float _progressToGoStarted = 0.0f;
	        
	        /**
	         * For auto scroll animation
	         */
	        float _dtSum = 0.0f;
			
			/**
			 *
			 */
			float _deltaDrag;
			
			/**
			 * store the position of the last touch down event
			 * received by the scrollview
			 */
			Point _touchDownPosition;
			
			/**
			 * store the previous touch event
			 */
			Point _previousTouchEventPosition;
			
			/**
			 * current speed of autoscroll
			 */
			bool _inertia;
			
			/**
			 *
			 */
			float _scrollSpeed;
            
            /**
             *
             */
            bool _ignoreTouches = false;
			
			/**
			 * scroll margin
			 * it's the number of points to swipe before the ScrollView begin to actually scroll
			 */
			float _scrollMargin;
			
			/**
			 * size of the scrollable content
			 * X (horizontal) or Y (vertical)
			 * the MIN limit of a scrollview is 0
			 * this attribute is the MAX limit
			 * and it is updated each time a new child is added
			 */
			Size _scrollableContentSize;
		};
	}
}


#endif




