//
//  Size.h
//  pxlframework
//
//  Created by Adrien Duermaël on 8/15/13.
//
//


#ifndef __pxlframework__Size__
#define __pxlframework__Size__


namespace px
{
	namespace engine
	{
		class Size
		{
			
		public:			
			/**
			 *
			 */
			Size() :
			_width(0.0f),
			_height(0.0f)
			{
			};
			
			/**
			 *
			 */
			virtual ~Size()
			{
			};
			
			/**
			 *
			 */
			Size( const float width, const float height ) :
			_width( width ),
			_height( height )
			{
			};
			
			/**
			 *
			 */
			Size( const Size& size ) :
			_width( size._width ),
			_height( size._height )
			{
			};
			
			/**
			 *
			 */
			Size& operator=( const Size& size )
			{
				_width = size._width;
				_height = size._height;
				
				return *this;
			};
			
			Size& operator*=( const float& coef )
			{
				_width *= coef;
				_height *= coef;
				
				return *this;
			};
			
			
#pragma mark - Accessors -
			
			inline float getWidth() const          { return _width; }
			inline void setWidth( float width )    { _width = width; }
			inline float getHeight() const         { return _height; }
			inline void setHeight( float height )  { _height = height; }
			inline void set( float width, float height )  { _width = width; _height = height; }
			
			
		private:
			/** in points */
			float _width;
			
			/** in points */
			float _height;
			
		};
	}
}


#endif




