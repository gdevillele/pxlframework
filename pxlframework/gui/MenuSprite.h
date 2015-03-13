//
//  MenuElement.h
//  pxlframework
//
//  Created by Gaëtan de Villèle on 8/26/13.
//
//


#ifndef __pxlframework__MenuElement__
#define __pxlframework__MenuElement__


// C++
#include <cassert>
#include <vector>
// pxlframework
#include "Sprite.h"
#include "../types/Point.h"
// px::tools
#include "Device.h"
#include "TouchEvent.h"


namespace px
{
	namespace engine
	{
		/**
		 * It represents an displayable element
		 * that can be contained in a Menu object
		 *
		 * It can only be place with a relative position
		 * based on screen or another MenuSprite
		 *
		 * a MenuSprite object always have an anchor point of (0.5,0.5)
		 *
		 * A Sprite can normaly contains other sprites, but MenuSprite
		 * can only contain MenuSprite objects
		 *
		 *
		 *
		 * - a MenuSprite object can only have relative positionning
		 * - in this class we use Sprite::_position as margin from the relative position
		 */
		class MenuSprite : public Sprite
		{
			
		public:
			
			typedef std::vector<MenuSprite*> MenuSpriteChildrenVector;
			
			enum class RelativePosition : uint8_t
			{
				UNDEFINED = 0,
				CENTER = 1,
				TOP = 2,
				RIGHT = 3,
				BOTTOM = 4,
				LEFT = 5,
				TOP_LEFT = 6,
				TOP_RIGHT = 7,
				BOTTOM_LEFT = 8,
				BOTTOM_RIGHT = 9
			};
			
			/**
			 * different status of a slider
			 * @brief this enum will be more global later (GUI)
			 */
			enum class State : uint8_t
			{
				NORMAL = 0,
				PRESSED = 1,
				FOCUSED = 2,
				DISABLED = 3,
			};
			
			
			
			/**
			 * convert values from the "MenuSpriteRelativePosition" enumeration into anchor point
			 */
			static Point convertRelativePositionIntoAnchorPoint(RelativePosition relativePosition);
			
			
			
			/**
			 * factory method
			 */
			static MenuSprite* newMenuSprite(const Size contentSize,
											 const RelativePosition relativePosition,
											 const RelativePosition anchor,
											 const Point& position);
			
			/**
			 * factory method
			 */
			static MenuSprite* newMenuSpriteWithTexture(const std::string& textureName,
														const RelativePosition relativePosition,
														const RelativePosition anchor,
														const Point& position);
			
			/**
			 * factory method without positionning infos for ScrollView widgets
			 */
			static MenuSprite* newMenuSprite(const std::string& textureName);
			
			
			
			/**
			 * Destructor
			 */
			virtual ~MenuSprite();
			
			
#pragma mark - Methods -
			
			/**
			 * GUI touch pipeline
			 * @return true if the touch is consumed
			 */
			virtual bool onTouch( TouchEvent event );
			
			/**
			 * convert touch event from [this->parent] coordinates
			 * into [this] coordinates (bottom left corner)
			 */
			TouchEvent convertTouchEventCoordinates( TouchEvent event );
			
			
			
#pragma mark - Accessors -
			
			/**
			 * returns the positionning mode
			 */
			const RelativePosition getRelativePosition() const {return _relativePosition;}
			const State getState() const {return _state;}
			const float getParallaxFactor() const {return _parallaxFactor;}
			const RelativePosition getAnchorToBeForcedTo() const {return _anchorToBeForcedTo;}
			/**
			 * compute on-screen bounding box
			 * the bounding box is relative to parent
			 * it contains position and the content size of the MenuSprite
			 *
			 * could be relative to parent (like CCNode in Cocos2D) .... not absolute
			 * and the click position could be transform in the parent landmark progressivelly
			 *
			 * (used to detect click)
			 */
			px::tools::Rect getBoundingBox();
			
			
			
#pragma mark - Modifiers -
			
			void setState(const State state) {_state = state;setChanged(true);}
			void setRelativePosition(RelativePosition relativePosition) {_relativePosition = relativePosition;}
			void setParallaxFactor(const float factor) {_parallaxFactor = factor;}
			void setAnchorToBeForcedTo(const RelativePosition anchor) {_anchorToBeForcedTo = anchor;}
			
            
            inline bool isScaledToFitDeviceResolution(){ return _scaledToFitDeviceResolution; }
            inline void setScaledToFitDeviceResolution(){ _scaledToFitDeviceResolution = true; }
			
			
		protected:
			
			bool init(const Size contentSize,
					  const RelativePosition relativePosition,
					  const RelativePosition anchor,
					  const Point& position);
			
			/**
			 * Default Constructor
			 * only this class and its sub classes can use it
			 */
			MenuSprite();
			
			/**
			 * current state of the widget
			 */
			State _state;
			
			
			
		private:
			
			/**
			 * relative positionning mode
			 * it defines the relative positionning in its parent
			 * it defines wich parent's point will be used as parent's
			 * anchor for this particular child
			 */
			RelativePosition _relativePosition;
			
			/**
			 * factor applied to the menusprite movements
			 * @brief use to do parallax in ScrollView. Value is 1.0f by default.
			 */
			float _parallaxFactor;
			
			/**
			 * anchor to be forced to on setContentSize(...)
			 */
			RelativePosition _anchorToBeForcedTo;
            
            
            /**
             * Has to be set to trus if device is already scaled to fit device's resolution
             * to avoid children from scaling, again (already scaled in cascade)
             * if parent is already scaled, child should set _scaledToFitDeviceResolution = true;
             */
            bool _scaledToFitDeviceResolution;
			
			
			/** Disable copying */
			DISALLOW_COPY_AND_ASSIGN(MenuSprite);
			
		};
	}
}


#endif




