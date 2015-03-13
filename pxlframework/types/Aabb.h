//
//  Aabb.h
//  pxlframework
//
//  Created by Pablo Gonzalez on 1/14/14.
//
//


#ifndef __pxlframework__Aabb__
#define __pxlframework__Aabb__


#include "Point.h"


namespace px
{
	namespace engine
	{
		class AABB
		{
		public:
			AABB( const Point& min, const Point& max );
			AABB( float minX, float minY, float maxX, float maxY );
			AABB( const AABB& aabb );
			
			bool contains( const Point& p ) const;
			bool contains( const AABB& aabb ) const;
			bool intersects( const AABB& aabb ) const;
			
			inline const Point& getMin() const { return _min; }
			inline const Point& getMax() const { return _max; }
			
			inline float getWidth() const { return _max.getX2D() - _min.getX2D(); }
			inline float getHeight() const { return _max.getY2D() - _min.getY2D(); }
			
			Point getCenter() const { return Point( (_min.getX2D() + _max.getX2D()) * .5f, (_min.getY2D() + _max.getY2D()) * .5f ); }
			
			AABB operator+(const Point moveBy) const;
			
		protected:
			Point _min, _max;
			
		private:
			AABB() {}
		};
	}
}


#endif




