//
//  Sprite.cpp
//  pxlframework
//
//  Created by Adrien Duermaël on 8/20/13.
//
//


#include "Sprite.h"

// C++
#include <cassert>
#include <iostream>
#include <math.h>
#include <algorithm>
// px::tools
#include "fs.h"


namespace px
{
	namespace engine
	{
		std::deque<void *> Sprite::rendererInstancesToRemove;
		
		enum ePackIndex
		{
			POSITION = 0,
		};
		
		
		
		Sprite* Sprite::newSprite()
		{
			Sprite* sprite = new Sprite();
			sprite->setType(Type::NOTEXTURE);
			return sprite;
		}
		
		
		
		Sprite* Sprite::newSpriteWithSize(Size contentSize)
		{
			Sprite* sprite = new Sprite();
			sprite->setType(Type::NOTEXTURE);
			sprite->setContentSize(contentSize);
			return sprite;
		}
		
		
		
		Sprite* Sprite::newSpriteWithTexture(const std::string& textureName)
		{
			Sprite *sprite = new Sprite();
			sprite->_textureName = textureName;
			return sprite;
		}
		
		/*static*/
		Sprite* Sprite::withSprite(const Sprite *o)
		{
			Sprite *sprite = new Sprite();
			if(! sprite->init(o))
			{
				delete sprite;
				sprite = nullptr;
				PXL_ASSERT(false);
			}
			return sprite;
		}
		
		
#pragma mark - Constructor / Destructor -
		
		Sprite::Sprite() :
		_type(Type::REGULAR),
		_parent(nullptr),
		_children(),
		_rendererInstance(nullptr),
		_anchor({0.5f, 0.5f}),
		_nbFrames(1),
		_frameColumns(1),
		_frameRows(1),
		_currentFrame(0),
		_rotation(0),
		_scale({1.0f, 1.0f}),
		_opacity(1.0f),
		_textureRect(0.0f, 0.0f, 1.0f, 1.0f),
		_clipRect(0.0f, 0.0f, 0.0f, 0.0f),
		_clipped(false),
		_parallax(0.0f),
		_contentSize(0.0f, 0.0f),
		_color({255, 255, 255, 255}),
		_changed(true),
		_visible(true)
		{}

		bool Sprite::init(const Sprite *o)
		{
			_textureName  = o->_textureName;
			_position     = o->_position;
			_anchor       = o->_anchor;
			_nbFrames     = o->_nbFrames;
			_frameRows    = o->_frameRows;
			_frameColumns = o->_frameColumns;
			_parallax     = o->_parallax;
			_textureRect  = {0.0f, 0.0f, 1.0f/_frameColumns, 1.0f/_frameRows};
			_contentSize = o->_contentSize;
			
			return _textureName != "";
		}
		
		/*virtual*/
		Sprite::~Sprite()
		{
			stopRendering();
			
			// if this Sprite had children we destroy them
			for(Sprite* child : _children)
			{
				delete child;
			}
			
			_children.clear();
		}
		
		void Sprite::setFlip( const bool flipHorizontal, const bool flipVertical )
		{
			if(isFlippedX() != flipHorizontal)
			{
				_scale.setX2D(- _scale.getX2D());
			}
			
			if(isFlippedY() != flipVertical)
			{
				_scale.setY2D(- _scale.getY2D());
			}
			
			_changed = true;
		}
		
		const bool Sprite::isFlippedX() const
		{
			return _scale.getX2D() < 0.0f;
		}
		
		const bool Sprite::isFlippedY() const
		{
			return _scale.getY2D() < 0.0f;
		}
		
		void Sprite::setFrameInfos( const uint8_t nbFrames, const uint8_t frameColumns, const uint8_t frameRows )
		{
			_nbFrames = nbFrames;
			_frameColumns = frameColumns;
			_frameRows = frameRows;
			
			_textureRect = {0.0f, 0.0f, 1.0f / _frameColumns, 1.0f / _frameRows};
		}
		
		void Sprite::setRotation( const Sprite::Angle rotation)
		{
			_rotation = rotation;
			_changed = true;
		}
		
		const Sprite::Angle Sprite::getRotation() const
		{
			return _rotation;
		}
		
		void Sprite::setScale(const Sprite::Scale scale)
		{
			// Keep the sign of "_scale" and the magnitude of "scale" (flip if necessary)
			float newScaleX = scale.getX2D();
			if ((_scale.getX2D() < 0.0f && newScaleX >= 0.0f) || (_scale.getX2D() >= 0.0f && newScaleX < 0.0f))
			{
				newScaleX = -newScaleX;
			}
			float newScaleY = scale.getY2D();
			if ((_scale.getY2D() < 0.0f && newScaleY >= 0.0f) || (_scale.getY2D() >= 0.0f && newScaleY < 0.0f))
			{
				newScaleY = -newScaleY;
			}
			_scale = {newScaleX,newScaleY};
			// previous exotic code :
			//_scale = {std::copysign(scale.getX2D(), _scale.getX2D()), std::copysign(scale.getY2D(), _scale.getY2D())};
			
			_changed = true;
		}
		const Sprite::Scale Sprite::getScale() const
		{
			return _scale;
		}
		
		void Sprite::stopRendering()
		{
			if (_rendererInstance != nullptr)
			{
				Sprite::rendererInstancesToRemove.push_back(_rendererInstance);
				_rendererInstance = nullptr;
				
				forceChildrenRenderingInstancesToNull();
			}
		}
		
		
		void Sprite::forceChildrenRenderingInstancesToNull()
		{
			for(Sprite* child : _children)
			{
				child->forceChildrenRenderingInstancesToNull();
				
				if (child->getRendererInstance() != nullptr)
				{
					child->setRendererInstance(nullptr);
				}
			}
		}
		
		
		
		const std::string& Sprite::getTextureName() const
		{
			return _textureName;
		}
		
		
		
		void Sprite::addChild( Sprite* child )
		{
			PXL_ASSERT(child != nullptr);
			PXL_ASSERT(child->getParent() == nullptr);
			_children.push_back(child);
			child->setParent(this);
		}
		
		
		void Sprite::clip(const px::tools::Rect r)
		{
			if (_type == Type::NOTEXTURE)
			{
				_clipped = true;
				_clipRect = r;
			}
			else
			{
				PXL_ASSERT(false);
			}
		}
		
		void Sprite::unclip()
		{
			_clipped = false;
		}
		
		
		
		
		
		bool Sprite::removeChild(Sprite* child, bool del)
		{
			PXL_ASSERT(child != nullptr);
			PXL_ASSERT(child->getParent() != nullptr);
			bool result = false;
			
			std::vector<Sprite*>::iterator it = std::find(_children.begin(), _children.end(), child);
			
			if (it != _children.end())
			{
				_children.erase(it);
				
				if (del)
				{
					delete child;
				}
				else
				{
					child->setParent(nullptr);
					child->stopRendering();
				}
				
				result = true;
			}
			
			/*for (std::vector<Sprite*>::iterator it = _children.begin(); it != _children.end(); ++it)
			 {
			 Sprite* current = (*it);
			 if (current == child)
			 {
			 it = _children.erase(it);
			 result = true;
			 break;
			 }
			 }*/
			
			
			return result;
		}
		
		
        void Sprite::removeAllChildren(bool del)
        {
            Sprite* child;
            
            while (!_children.empty())
            {
                child = _children.back();
                _children.pop_back();
                
                if (del)
                {
                    delete child;
                }
                else
                {
                    child->setParent(nullptr);
                    child->stopRendering();
                }
            }
        }
        
        
		
		Sprite* Sprite::getParent() const
		{
			return _parent;
		}
		
		const std::vector<Sprite*>& Sprite::getChildren() const
		{
			return _children;
		}
		
		void Sprite::setParent(Sprite* parent)
		{
			_parent = parent;
		}
		
		void Sprite::setPosition( const Point& position )
		{
			_position = position;
			_changed = true;
		}
		
		void Sprite::setCurrentFrame( const uint8_t currentFrame )
		{
			_changed = true;
			
			// check the new frame number is not out of the frames array bounds
			PXL_ASSERT(currentFrame < _nbFrames);
			
			_currentFrame = currentFrame;
			
			// Set the correct rect
			float textureOffsetX = _currentFrame % _frameColumns;
			float textureOffsetY = _currentFrame / _frameColumns;
			
			// _textureRect._witdh and _textureRect._height never change
			_textureRect.setX(textureOffsetX * _textureRect.getWidth());
			_textureRect.setY(textureOffsetY * _textureRect.getHeight());
		}
		
		void Sprite::setTextureRect( const px::tools::Rect textureRect )
		{
			_changed = true;
			_textureRect = textureRect;
		}
		
		
		/* virtual */ void Sprite::tick(const Tick::Duration dt)
		{
			for (Sprite *s : _children)
			{
				s->tick(dt);
			}
			Action_Receiver::tick(dt);
		}
	}
}




