//
//  Sprite.h
//  pxlframework
//
//  Created by Adrien Duermaël on 8/20/13.
//
//


#ifndef __pxlframework__Sprite__
#define __pxlframework__Sprite__


// C++
#include <string>
#include <vector>
#include <deque>
#include <cinttypes>
// pxlframework
#include "macros.h"
#include "utils/utils.h"
#include "Tick.h"
#include "types/Point.h"
#include "types/Size.h"
#include "utils/ColorUtils.h"
#include "actions/Action_Receiver.h"
// px::tools
#include <Rect.h>


namespace px
{
	namespace engine
	{
        typedef RGBAColor Color;
    
		class Sprite : public Action_Receiver
		{
		public:
			/**
			 * Type for the rotation of a sprite, in radians
			 */
			typedef float Angle;
			
			/**
			 * Type for the scale of a sprite
			 */
			typedef Point Scale;
			
			/**
			 * list of the different types a Sprite
			 * (and sub-types) typed object can have
			 */
			enum class Type : uint8_t
			{
				REGULAR = 1,  // regular sprite with a texture (default)
				LABEL = 2,    // sprite with a texture from a font
				NOTEXTURE = 3 // sprite without any texture
			};
			
			/**
			 * When a Sprite gets removed, if a rendererInstance pointer was defined,
			 * it has to be pushed in that vector.
			 * Instances pointers will be removed from that vector by the renderer
			 * itself when removing instances from the rendering scene.
			 * @see stopRendering()
			 * First instance in that deque, should be the first out.
			 * To avoid a child to be removed, after its own parent.
			 */
			static std::deque<void*> rendererInstancesToRemove;
			
			/**
			 * Factory method
			 * no sprite / no size
			 */
			static Sprite* newSprite();
			
			/**
			 * Factory method
			 * no sprite
			 */
			static Sprite* newSpriteWithSize(const Size contentSize);
			
			/**
			 * Factory method
			 */
			static Sprite* newSpriteWithTexture(const std::string& textureName);
			
			/**
			 * Factory method
			 */
			static Sprite* withSprite(const Sprite* original);
			
			/**
			 * Destructor
			 */
			virtual ~Sprite();
			
			/**
			 * Just call that method when you want to stop displaying a Sprite.
			 * The Sprite object remains of course, but the instance created by the renderer will be destroyed.
			 */
			void stopRendering();
			
			/*
			 * This recursive method is called in stopRendering() to avoid rendering instances to be removed twice by the renderer.
			 * When the renderer destroys a rendering instance, all children of that instance get destroyed at the same time.
			 * So we don't have to ask for them to be destroyed once again. (it could crash depending on the renderer in charge)
			 */
			void forceChildrenRenderingInstancesToNull();
			
			/**
			 * Add a child to this Sprite
			 */
			virtual void addChild(Sprite* child);
			
			
			/**
			 * remove a child
			 * @return whether the child has been found and removed
			 */
			virtual bool removeChild(Sprite* child, bool del = true);
            
            /**
             * remove all children
             */
            virtual void removeAllChildren(bool del = true);
            
			
			/**
			 * Sprite is an Action Receiver, but tick needs to be propagated to children
			 */
			virtual void tick(const Tick::Duration dt);
			
#pragma mark - Accessors -
			
			const Type getType() const {return _type;}
			
			/**
			 * return a pointer on the parent of this Sprite instance
			 */
			virtual Sprite* getParent() const;
			
			/**
			 * return a reference on the array of children
			 */
			virtual const std::vector<Sprite*>& getChildren() const;
			
			const std::string& getTextureName() const;
			inline void* getRendererInstance() const {return _rendererInstance;}
			inline const Point getPosition() const { return _position; }
			inline const Point& getAnchor() const { return _anchor; }
			inline const uint8_t getNbFrames() const { return _nbFrames; }
			inline const uint8_t getCurrentFrame() const { return _currentFrame; }
			const bool isFlippedX() const;
			const bool isFlippedY() const;
			const Sprite::Angle getRotation() const;
			const Sprite::Scale getScale() const;
			inline float getOpacity() const {return _opacity;}
			/// Returns the rect of the Sprite in percentage
			inline const px::tools::Rect& getTextureRect() const { return _textureRect; }
			inline const uint8_t getframeColumns() const {return _frameColumns;}
			inline const uint8_t getFrameRows() const {return _frameRows;}
			/**
			 * indicate whether this object has children
			 * @return a boolean, true if it has children, false if no child
			 */
			bool getHasChildren() const {return ! _children.empty();}
			/// @todo fixme doesnt work and we shouldnt have this method ....
			inline const Size getContentSize() const {return _contentSize;}
			
			const RGBAColor& getColor() const {return _color;}
			/// indicates whether the sprite need to be refreshed
			const bool getChanged() const {return _changed;}
			inline const float getParallax() const {return _parallax;}
			
			inline bool isClipped() const { return _clipped; }
			inline const px::tools::Rect& getClipRect() const { return _clipRect; }
			
			
#pragma mark - Modifiers -
			
			void setType(const Type type) {_type = type;}
			/// define the renderer instance pointer for the Sprite object
			inline void setRendererInstance(void* rendererInstance) {_rendererInstance = rendererInstance;_changed=true;}
			virtual void setPosition(const Point& position);
			inline void setAnchor( const float x, const float y ) {_anchor.set2D(x,y);_changed=true;}
			inline void setAnchor( const Point& anchor ) {_anchor = anchor;_changed=true;}
			void setFrameInfos(const uint8_t nbFrames, const uint8_t frameColumns, const uint8_t frameRows);
			void setCurrentFrame (const uint8_t currentFrame);
			void setTextureRect( const px::tools::Rect textureRect );
			void setFlip(const bool flipHorizontal, const bool flipVertical);
			void setRotation(const Sprite::Angle rotation);
			inline void setScale(const float scale){setScale({scale, scale});};
			void setScale(const Sprite::Scale scale);
			/// Opacity, 0.0f is full transparent, 1.0f full opaque
			inline void setOpacity(float opacity) {_opacity=opacity; for (Sprite* child :_children){ child->setOpacity(opacity); };_changed=true;}
			virtual void setContentSize(const Size size) {_contentSize = size;_changed=true;}
			inline void setColor(const RGBAColor& color) {_color = color; _changed=true;}
			inline void setChanged(const bool changed) {_changed = changed;}
			/// Set the maximum parallax effect in points
			inline void setParallax(const float maxValue) {_parallax = maxValue;}
			
			inline void setVisible( bool visible ) { _visible = visible; }
			inline bool isVisible() const { return _visible; }
			
			/**
			 * Clips a Sprite.
			 * Works only with NOTEXTURE type
			 */
			void clip(const px::tools::Rect r);
			
			/**
			 * To unclip a clipped Sprite
			 */
			void unclip();
			
			
#pragma mark - protected -
			
		protected:
			
			/**
			 * Default Constructor
			 * @see newWithTexture
			 */
			Sprite();
			/**
			 * initialisation by the factory method (cloning)
			 */
			bool init(const Sprite *o);

			/**
			 * set the sprite parent
			 */
			virtual void setParent( Sprite* parent );
			
			/**
			 *
			 */
			inline void setTextureName( const std::string& textureName )
			{
				PXL_ASSERT(!textureName.empty());
				_textureName = textureName;
			}
			
			/** children sprites of the current sprite */
			std::vector<Sprite*> _children;
			
			/** Anchor point for the sprite, ie. the "center" we want for the animations, positioning, etc.*/
			Point _anchor;
			
			/**
			 * size of the renderer instance of the Sprite
			 * in game points
			 * as long as the Sprite object does not have a renderer instance
			 * this variable should be { 0, 0 }
			 * IMPORTANT : this value can be set or NOT by the renderer! (be careful)
			 */
			Size _contentSize;
			
			/** Position of the sprite, relative to its worldElement */
			Point _position;
			
#pragma mark - private -
			
		private:
			
			Type _type;
			
			/** parent sprite of the current sprite object */
			Sprite* _parent;
			
			/** A pointer to an instance, created by the renderer for that element.
			 * Instanciated when by the renderer when it needs to display the element. */
			void* _rendererInstance;
			
			/** Name of the texture used, with the extension */
			std::string _textureName;
			
			/** The number of frames. 1 by default.
			 * More if we have frame animations */
			uint8_t _nbFrames;
			
			/** The number of frame columns. 1 by default. */
			uint8_t _frameColumns;
			
			/** The number of frame rows. 1 by default. */
			uint8_t _frameRows;
			
			/**
			 * The current frame to be displayed. 0 by default.
			 * This value is between [ 0 ] (included) and [ _nbFrame - 1 ] (included)
			 */
			uint8_t _currentFrame;
			
			/** The sprite rotation, in radians */
			Sprite::Angle _rotation;
			
			/** Value of parallax (max)*/
			float _parallax;
			
			/** The sprite scale, in percentage of the original size
			 * This used to know is flipped or not, horizontaly, verticaly or both.
			 * (1,1) -> not flipped
			 * (-1,1) -> flipped horizontally
			 * (1,-1) -> flipped verticaly
			 * (-1,-1) -> flipped both horizontally and vertically
			 */
			Sprite::Scale _scale;
			
			/** The zone to use on the texture
			 * Sprite object doesn't know about rendering instance details.
			 * So frame size is define as a percentage of the rendered texture */
			px::tools::Rect _textureRect;
			
			/**
			 * Renderer can use that information to clip the sprite (and children)
			 * Only used with NOTEXTURE Sprites.
			 * Rect is in points, position depends on Sprite anchor point
			 */
			px::tools::Rect _clipRect;
			bool _clipped;
			
			/** Opacity, 0.0f is full transparent, 1.0f full opaque */
			float _opacity;
			
			/** color of the sprite */
			RGBAColor _color;
			
			/**
			 * indicate whether the menuSprite object has changed and
			 * needs to have its renderer instance updated
			 */
			bool _changed;
			
			/**
			 * indicates whether the sprite should be rendered or not
			 */
			bool _visible;
			
			/** Disable copying */
			DISALLOW_COPY_AND_ASSIGN(Sprite);
			
		};
	}
}


#endif




