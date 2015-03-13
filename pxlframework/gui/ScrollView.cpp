//
//  ScrollView.cpp
//  pxlframework
//
//  Created by Gaëtan de Villèle on 12/12/13.
//
//


#include "ScrollView.h"

// px::tools
#include "PXLAlgorithm.h"


namespace px
{
	
	namespace engine
	{
		
#pragma mark - Instance creation -
		
		
		ScrollView* ScrollView::newScrollView(const Size contentSize,
											  const MenuSprite::RelativePosition relativePosition,
											  const MenuSprite::RelativePosition anchor,
											  const Point& position,
											  const Orientation orientation,
											  const float scrollableContentSize,
											  const float scrollMargin)
		{
			ScrollView* result = new ScrollView();
			if (result->init(contentSize, relativePosition, anchor, position, orientation, scrollableContentSize, scrollMargin) == false)
			{
				delete result;
				result = nullptr;
			}
			return result;
		}
		
		
		
#pragma mark - Constructor / Destructor -
		
		ScrollView::ScrollView() : MenuSprite(),
		_state(State::IDLE),
		_orientation(Orientation::UNKNOWN),
		_progress(0),
		_touchDownPosition(0,0),
		_inertia(false),
		_scrollSpeed(0.0f),
		_scrollableContentSize(0.0f,0.0f),
		_deltaDrag(0.0),
		_scrollMargin(0.0f)
		{}
		
		
		
		ScrollView::~ScrollView()
		{}
		
		
		
#pragma mark - Public Methods -
		
		
		void ScrollView::tick(const Tick::Duration dt)
		{
			// call the supersuperclass tick() method
			// to have animations played on children
			Sprite::tick(dt);
			
	        // refresh the child nodes' positions
			refreshChildrenPosition(dt);
		}
		
		
		
		void ScrollView::addChild(Sprite* child)
		{
			// call the base class method
			Sprite::addChild(child);
		}
		
		
		
		bool ScrollView::onTouch(TouchEvent event)
		{
            if(_ignoreTouches)
            {
                MenuSprite::onTouch(event);
                return true;
            }
            
			// this variable is returned at the
			bool result = false;
			
			// move touch event into the scrollview inner coordinates
			// a touch on the bottom left corner of the scrollview
			// will have coordinates [0,0]
			TouchEvent localevent = convertTouchEventCoordinates(event);
			
			// get event data
			const TouchEvent::Type eventType = localevent.getType();
			const float eventX = localevent.getX();
			const float eventY = localevent.getY();
			
			// test if the touch event is on the view
			if (eventX > 0 && eventX < getContentSize().getWidth() &&
			    eventY > 0 && eventY < getContentSize().getHeight())
			{
				if (eventType == TouchEvent::Type::DOWN)
				{
					// if the menusprite state is normal, it can handle touches
					if (MenuSprite::getState() == MenuSprite::State::NORMAL)
					{
						if (getState() == State::IDLE)
						{
							_inertia = false;
							// update the ScrollView::State attribute
							setState(State::TOUCHED_DOWN);
							// update the position of the last touch down event
							_touchDownPosition.set2D(eventX, eventY);
							// transmit the touch down to scrollview children
							MenuSprite::onTouch(event);
							// we consume the TouchEvent
							result = true;
						}
						else if (getState() == State::TOUCHED_DOWN)
						{
							// nothing
						}
						else if (getState() == State::USERSCROLLING)
						{
							// nothing
						}
					}
				}
				else if (eventType == TouchEvent::Type::MOVE)
				{
					// if the menusprite state is normal, it can handle touches
					if (MenuSprite::getState() == MenuSprite::State::NORMAL)
					{
						if (getState() == State::IDLE)
						{
							// nothing
						}
						else if (getState() == State::TOUCHED_DOWN)
						{
							// compute the distance between the last touch down
							// position and the current touch move position
							float squareDistance = _touchDownPosition.distanceSquaredWith(eventX, eventY);

							if (squareDistance < _scrollMargin)
							{
								// touch move event is still in the sensitivity area
								// the scroll view doesn't move
								// it still can be a click on a scroll view child
								// we transmit the touch move to scrollview children
								MenuSprite::onTouch(event);
							}
							else
							{
	                            TouchEvent cancelEventForChildren = TouchEvent(TouchEvent::Type::CANCEL, event.getX(), event.getY());
	                            MenuSprite::onTouch(cancelEventForChildren);
	                            
								if ((getOrientation() == Orientation::HORIZONTAL && getScrollableContentSize().getWidth() > getContentSize().getWidth()) ||
									(getOrientation() == Orientation::VERTICAL   && getScrollableContentSize().getHeight() > getContentSize().getHeight()))
								{
										// we switch to dragging state
										// and we transmit a "touch cancel" event to children
										setState(State::USERSCROLLING);
								}
							}
						}
						else if (getState() == State::USERSCROLLING)
						{
							// compute the delta between the previous touch event and the current touch event
							Point delta(_previousTouchEventPosition.getX2D() - eventX,
										_previousTouchEventPosition.getY2D() - eventY);
							// --- Horizontal ---
							// negative when moving finger from left to right
							// positive when moving finger from right to left
							// --- Vertical ---
							// positive when moving finger from top to bottom
							// negative when moving finger from bottom to top
							
							
							if (getOrientation() == Orientation::VERTICAL)
							{
								// delta value is NEGATIVE when we scroll the vertical scrollview from the beginning to the end
								_deltaDrag -= delta.getY2D();
							}
							else if (getOrientation() == Orientation::HORIZONTAL)
							{
								// delta value is POSITIVE when we scroll the vertical scrollview from the beginning to the end
								_deltaDrag += delta.getX2D();
							}
						}
					}
				}
				else if (eventType == TouchEvent::Type::UP)
				{
					if (_state == State::IDLE)
					{
						// nothing
					}
					else if (_state == State::TOUCHED_DOWN)
					{
						// scroll view is not dragging
						// so we still transmit touch events to children
						MenuSprite::onTouch(event);
						setState(State::IDLE);
					}
					else if (_state == State::USERSCROLLING)
					{
						// if scroll view is dragging, we stop dragging it
						setState(State::IDLE);
						_inertia = true;
						_deltaDrag = 0.0f;
					}
				}
			}
			else // the touch event is NOT on this widget
			{
				if (eventType == TouchEvent::Type::DOWN)
				{
					if (getState() == ScrollView::State::AUTOSCROLLING ||
						getState() == ScrollView::State::DIRECTSCROLL ||
						getState() == ScrollView::State::IDLE)
					{
						// ignore it, do nothing
					}
					else if (getState() == ScrollView::State::UNDEFINED ||
							 getState() == ScrollView::State::TOUCHED_DOWN ||
							 getState() == ScrollView::State::USERSCROLLING)
					{
						setState(State::IDLE);
					}
				}
				else if(eventType == TouchEvent::Type::MOVE)
				{
					// if user is currently scrolling,
					// we allow him to continue to scroll
					// outside on the scrollview viewport
					if (getState() == ScrollView::State::AUTOSCROLLING ||
						getState() == ScrollView::State::DIRECTSCROLL ||
						getState() == ScrollView::State::IDLE)
					{
						// ignore it, do nothing
					}
					else if (getState() == ScrollView::State::TOUCHED_DOWN)
					{
						// compute the distance between the last touch down
						// position and the current touch move position
						float squareDistance = _touchDownPosition.distanceSquaredWith(eventX, eventY);
						
                        if (squareDistance < _scrollMargin)
						{
							// touch move event is still in the sensitivity area
							// the scroll view doesn't move
							// it still can be a click on a scroll view child
							// we transmit the touch move to scrollview children
							MenuSprite::onTouch(event);
						}
						else
						{
							TouchEvent cancelEventForChildren = TouchEvent(TouchEvent::Type::CANCEL, event.getX(), event.getY());
							MenuSprite::onTouch(cancelEventForChildren);
							
							if ((getOrientation() == Orientation::HORIZONTAL && getScrollableContentSize().getWidth() > getContentSize().getWidth()) ||
								(getOrientation() == Orientation::VERTICAL   && getScrollableContentSize().getHeight() > getContentSize().getHeight()))
							{
								// we switch to dragging state
								// and we transmit a "touch cancel" event to children
								setState(State::USERSCROLLING);
							}
						}
					}
					else if (getState() == ScrollView::State::UNDEFINED)
					{
						setState(State::IDLE);
					}
					else if (getState() == ScrollView::State::USERSCROLLING)
					{
						// compute the delta between the previous touch event and the current touch event
						Point delta(_previousTouchEventPosition.getX2D() - eventX,
									_previousTouchEventPosition.getY2D() - eventY);
						// --- Horizontal ---
						// negative when moving finger from left to right
						// positive when moving finger from right to left
						// --- Vertical ---
						// positive when moving finger from top to bottom
						// negative when moving finger from bottom to top
						
						
						if (getOrientation() == Orientation::VERTICAL)
						{
							// delta value is NEGATIVE when we scroll the vertical scrollview from the beginning to the end
							_deltaDrag -= delta.getY2D();
						}
						else if (getOrientation() == Orientation::HORIZONTAL)
						{
							// delta value is POSITIVE when we scroll the vertical scrollview from the beginning to the end
							_deltaDrag += delta.getX2D();
						}
					}
				}
				else if(eventType == TouchEvent::Type::UP)
				{
					if (getState() == ScrollView::State::AUTOSCROLLING ||
						getState() == ScrollView::State::DIRECTSCROLL ||
						getState() == ScrollView::State::IDLE)
					{
						// ignore it, do nothing
					}
					else if (getState() == ScrollView::State::UNDEFINED ||
							 getState() == ScrollView::State::TOUCHED_DOWN)
					{
						setState(State::IDLE);
					}
					else if (getState() == ScrollView::State::USERSCROLLING)
					{
						setState(State::IDLE);
						_inertia = true;
						_deltaDrag = 0.0f;
					}
				}
			}
			
			// store the position of the touch event we just handled
			// in the _previousTouchEventPosition variable
			_previousTouchEventPosition.set2D(eventX, eventY);
			
			return result;
		}
		
		
#pragma mark modifiers
		
		void ScrollView::setOrientation(Orientation orientation)
		{
			if (_orientation == Orientation::UNKNOWN)
			{
				_orientation = orientation;
			}
			else
			{
				// if the orientation of the ScrollView is already set, we crash
				// it's not possible to change the orientation of a ScrollView after its creation
				PXLLOG("[ScrollView::setOrientation] [ERROR] it's not possible to override the orientation");
				PXL_ASSERT(false);
			}
		}
		
		
		
		void ScrollView::autoscrollTo(float progress)
		{
	        if(progress < 0) progress = 0.0f;
	        
            float maxScroll = 0.0f;
            
            if (_orientation == Orientation::HORIZONTAL)
            {
                maxScroll = _scrollableContentSize.getWidth() - _contentSize.getWidth();
            }
            else if (_orientation == Orientation::VERTICAL)
            {
                maxScroll = _scrollableContentSize.getHeight() - _contentSize.getHeight();
            }
            
            if (maxScroll < 0.0f) maxScroll = 0.0f;
            
            if (progress > maxScroll)
            {
                progress = maxScroll;
            }
            
	        _progressToGoStarted = _progress;
	        _progressToGo = progress;
	        _dtSum = 0.0f;
	        _state = State::AUTOSCROLLING;
		}
        
        void ScrollView::setProgress(float progress)
		{
            if(progress < 0) progress = 0.0f;
	        
            float maxScroll = 0.0f;
            
            if (_orientation == Orientation::HORIZONTAL)
            {
                maxScroll = _scrollableContentSize.getWidth() - _contentSize.getWidth();
            }
            else if (_orientation == Orientation::VERTICAL)
            {
                maxScroll = _scrollableContentSize.getHeight() - _contentSize.getHeight();
            }
            
            if (maxScroll < 0.0f) maxScroll = 0.0f;
            
            if (progress > maxScroll)
            {
                progress = maxScroll;
            }
	        
	        _progressToGo = progress;
            _state = State::DIRECTSCROLL;
        }
		
		
		
#pragma mark - protected methods -
		
		
		bool ScrollView::init(const Size contentSize,
							  const MenuSprite::RelativePosition relativePosition,
							  const MenuSprite::RelativePosition anchor,
							  const Point& position,
							  const Orientation orientation,
							  const float scrollableContentSize,
							  const float scrollMargin)
		{
			// Sprite stuff
			setType(Sprite::Type::NOTEXTURE);
			setContentSize(contentSize);
			
			// MenuSprite stuff
			setRelativePosition(relativePosition);
			setAnchor(MenuSprite::convertRelativePositionIntoAnchorPoint(anchor));
			setPosition(Point(position.getX2D(), position.getY2D()));
			
			// ScrollView stuff
			setOrientation(orientation);
			setScrollableContentSize(Size(scrollableContentSize, scrollableContentSize));
			setScrollMargin(scrollMargin);
	        
	        clip(px::tools::Rect(0,0,contentSize.getWidth(),contentSize.getHeight()));
			
			return true;
		}
		
		
		
#pragma mark - Private Methods -
		
		void ScrollView::refreshChildrenPosition(const Tick::Duration dt)
		{
			float distanceToApply = 0.0f;
			
			if (getState() == State::IDLE && _inertia == true)
			{
				distanceToApply = _scrollSpeed * dt;
				if (_scrollSpeed > 0)
				{
					if (_scrollSpeed > 100.0f)
					{
						_scrollSpeed -= (6000.0f+(_scrollSpeed*_scrollSpeed/5000.0f)) * dt;
					}
					else
					{
						_scrollSpeed = 0.0f;
						_inertia = false;
					}
				}
				else
				{
					if (_scrollSpeed < -100.0f)
					{
						_scrollSpeed += (6000.0f+(_scrollSpeed*_scrollSpeed/5000.0f)) * dt;
					}
					else
					{
						_scrollSpeed = 0.0f;
						_inertia = false;
					}
				}
			}
			else if (getState() == State::USERSCROLLING)
			{
				// we apply 100% of _deltaDrag each 0.032s
				float percentageToApply = std::min(dt / 0.032f, 1.0f);
				
				distanceToApply = _deltaDrag * percentageToApply;
				
				// compute speed
				_scrollSpeed = distanceToApply / dt;
				
				_deltaDrag -= distanceToApply;
			}
	        else if(_state == State::AUTOSCROLLING)
	        {
	            if(abs(_progressToGo - _progress) < 10.0f)
	            {
	                _state = State::IDLE;
	                distanceToApply = _progressToGo - _progress;
	            }
	            else
	            {
	                _dtSum += std::min(dt, 0.033f);
	                
	                auto p = px::tools::algorithm::cubic(_progressToGoStarted, _progressToGo, _dtSum);
	                
	                distanceToApply = p - _progress;
	            }
	        }
            else if(_state == State::DIRECTSCROLL)
            {
                // If the progression has been set progamatically
                distanceToApply = _progressToGo - _progress;
                _state = State::IDLE;
            }
			
			if (distanceToApply != 0)
			{
				_progress += distanceToApply;
				
				if (getOrientation() == ScrollView::Orientation::HORIZONTAL)
				{
					if (_progress < 0)
					{
						distanceToApply -= _progress;
						_progress = 0;
						_inertia = false;
						_deltaDrag = 0.0f;
					}
					else if (_progress > getScrollableContentSize().getWidth() - getContentSize().getWidth())
					{
						distanceToApply -= _progress - (getScrollableContentSize().getWidth() - getContentSize().getWidth());
						_progress = getScrollableContentSize().getWidth() - getContentSize().getWidth();
						_inertia = false;
						_deltaDrag = 0.0f;
					}
					
					for (Sprite* child : getChildren())
					{
						MenuSprite* msChild = static_cast<MenuSprite*>(child);
						Point currentPosition = child->getPosition();
						Point newPosition = Point(currentPosition.getX2D() - ((distanceToApply)*msChild->getParallaxFactor()),
																	currentPosition.getY2D());
						child->setPosition(newPosition);
					}
				}
				else if (getOrientation() == ScrollView::Orientation::VERTICAL)
				{
					if (_progress < 0)
					{
						distanceToApply -= _progress;
						_progress = 0;
						_inertia = false;
						_deltaDrag = 0.0f;
					}
					else if (_progress > getScrollableContentSize().getHeight() - getContentSize().getHeight())
					{
						distanceToApply -= _progress - (getScrollableContentSize().getHeight() - getContentSize().getHeight());
						_progress = getScrollableContentSize().getHeight() - getContentSize().getHeight();
						_inertia = false;
						_deltaDrag = 0.0f;
					}
					
					for (Sprite* child : getChildren())
					{
						MenuSprite* msChild = static_cast<MenuSprite*>(child);
						Point currentPosition = child->getPosition();
						Point newPosition = Point(currentPosition.getX2D(),
																	currentPosition.getY2D() + ((distanceToApply)*msChild->getParallaxFactor()));
						child->setPosition(newPosition);
					}
				}
			}
		}
	}
}




