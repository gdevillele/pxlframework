//
//  Point.h
//  pxlframework
//
//  Created by Adrien Duermaël on 8/12/13.
//
//


#ifndef __pxlframework__Point__
#define __pxlframework__Point__


// C++
#include <string>
#include <cmath>
#include <assert.h>


namespace px
{
	namespace engine
	{
		class Point
		{
			
		public:
			
#pragma mark - static -
			
			/**
			 * Create a Point from polar coordonates
			 * @param r the radius
			 * @param theta the angle in radian
			 */
			static Point createWithPolar(const float r, const float theta)
			{
				return {r * std::cos(theta), r * std::sin(theta)};
			}
			
			
			
#pragma mark - Constructor / Destructor -
			
			/**
			 * Default constructor
			 */
			Point();

			/**
			 * constructor with parameters
			 */
			Point(const float x, const float y);
			
			/**
			 * Destructor
			 */
			virtual ~Point();
			
			/**
			 * Copy constructors
			 * they are needed because we do not handle Point objects by reference but by copy
			 */
			Point(Point& other);
			Point(const Point& other);
			
			
			
#pragma mark - Public methods -
			
			/**
			 * Distance in the 2D world
			 */
			float distanceWith( const float x, const float y ) const;
			float distanceWith( const Point p ) const;
			
			/**
			 * Distance in the 2D world
			 */
			float distanceSquaredWith( const float x, const float y ) const;
			float distanceSquaredWith( const Point p ) const;
			
			/**
			 * Distance to {0,0} in the 2D world
			 */
			float distanceWithOrigin() const;
			
			
			
#pragma mark - Operators -
			
			Point operator  +  (const Point& v) const;
			Point operator  -  (const Point& v) const;
			void operator   += (const Point& v);
			void operator   -= (const Point& v);
			Point operator  /  (float s) const;
			Point operator  *  (float s) const;
			void operator   /= (float s);
			void operator   *= (float s);
			bool operator   == (const Point &v) const;
			inline operator std::string() const;
			Point& operator =  (const Point& other);

			
			
#pragma mark - Accessors -
			
			inline float getX2D() const {return _x;};
			inline float getY2D() const {return _y;};
			
			
			
#pragma mark - Modifiers -

			virtual void setX2D( const float x2d );
			virtual void setY2D( const float y2d );
			virtual void set2D( const float x2d, const float y2d );
			virtual void addX2D( const float x2D );
			virtual void addY2D( const float y2D );
			virtual void add2D( const float x2D, const float y2D );
			void set(const Point& point);
			
		protected:
			
			/** Point's abscissa */
			float _x;
			
			/** Point's ordinate */
			float _y;
						
		};
	}
}


#endif




