//
//  Label.h
//  pxlframework
//
//  Created by Gaëtan de Villèle on 10/30/13.
//
//


#ifndef __pxlframework__Label__
#define __pxlframework__Label__


// pxlframework
#include "MenuSprite.h"


namespace px
{
	namespace engine
	{
		class Label : public MenuSprite
		{
		public:
			
			/**
			 * add this label in a Menu / MenuSprite
			 */
			static Label* newLabel(const MenuSprite::RelativePosition relativePosition,
								   const MenuSprite::RelativePosition anchor,
								   const Point& position,
								   const std::string& text,
								   const std::string& font);
            
            static Label* newLabel(const MenuSprite::RelativePosition relativePosition,
                                   const MenuSprite::RelativePosition anchor,
                                   const Point& position,
                                   const std::string& text,
                                   const std::string& font,
                                   const float fontSize);
            
			
			/**
			 * to be used as a simple Sprite : add this label in a Sprite / WorldElement
			 */
			static Label* newLabel(const Point& anchor,
								   const Point& position,
								   const std::string& text,
								   const std::string& font);
            
            static Label* newLabel(const Point& anchor,
                                   const Point& position,
                                   const std::string& text,
                                   const std::string& font,
                                   const float fontSize);
            
			
			/**
			 * Destructor
			 */
			virtual ~Label();
			
			
			// ---------- ACCESSORS ----------
			
			/**
			 * Return text
			 */
			inline const std::string& getText() const {return _text;}
			
			inline const std::string& getFont() const { return _font; }
            
            inline const float getFontSize() const { return _fontSize; }
            
            inline const bool isBitmap() const { return _bitmap; }
			
			inline const float getMaxWidth() const { return _maxWidth; }
			
			
			// ---------- MODIFIERS ----------
			
			/**
			 * Define text
			 */
			void setText( const std::string& text )
			{_text = text;setTextChanged(true);}
			
			inline const bool getTextChanged() const {return _textChanged;}
			inline void setTextChanged(const bool changed) {setChanged(changed);_textChanged = changed;}
			
			
			inline const int getSizeToReserve() const {return _sizeToReserve;}
			inline void setSizeToReserve(const int sizeToReserve) {_sizeToReserve = sizeToReserve;}
			
			inline void setMaxWidth( float maxWidth ){ _maxWidth = maxWidth; }
            
            
            /**
             * Define font
             */
            inline void setFont( const std::string& font ){_font = font;}
            
            inline void setFontSize( float fontSize ){_fontSize = fontSize;}
            
            inline void setBitmap(){_bitmap = true;}
            inline void setTTF(){_bitmap = false;}
			
			
			
		protected:
			
			/**
			 * Default Constructor
			 */
			Label();
			
			
		private:
			
			/**
			 * text of the label
			 */
			std::string _text;
			
			/**
			 * TTF font name
             * or path to the bitmap font
			 */
			std::string _font;
            
            
            /**
             * Font size
             * Not directly related to the Sprite content size
             * The renderer decides how to interpret this size
             */
            float _fontSize;
            
            
            /**
             * Indicates if a bitmap font should be used
             * false by default
             */
            bool _bitmap;
			
			
			/**
			 * When rendering using Bitmap font, we may need to know the size to reserver.
			 * To avoid resizeing the texture atlas too much.
			 * Value is 0 by default
			 */
			int _sizeToReserve;
			
			/**
			 * Specific to Labels. To avoid big operation of updating the text rendering instance.
			 */
			bool _textChanged;
			
			/**
			 * Max width for texts with several lines
			 */
			float _maxWidth;
			
			
			/**
			 * Disable copying
			 */
			DISALLOW_COPY_AND_ASSIGN(Label);
		};
	}
}


#endif




