//
//  Aabb.cpp
//  pxlframework
//
//  Created by Pablo Gonzalez on 1/14/14.
//
//


#include "Aabb.h"
#include "utils.h"


namespace px
{
	namespace engine
	{
		AABB::AABB( const Point& min, const Point& max ) :
        _min( min ),
        _max( max )
		{
			PXL_ASSERT( min.getX2D() <= max.getX2D() && min.getY2D() <= max.getY2D() );
		}
		
		AABB::AABB( float minX, float minY, float maxX, float maxY )
		{
			PXL_ASSERT(minX == minX);
			PXL_ASSERT(minY == minY);
			PXL_ASSERT(maxX == maxX);
			PXL_ASSERT(maxY == maxY);
			
			PXL_ASSERT( minX <= maxX && minY <= maxY );
			
			_min = Point( minX, minY );
			_max = Point( maxX, maxY );
		}
		
		AABB::AABB( const AABB& aabb ) :
        _min( aabb._min ),
        _max( aabb._max )
		{
			PXL_ASSERT( _min.getX2D() <= _max.getX2D() && _min.getY2D() <= _max.getY2D() );
		}
		
		bool AABB::contains( const Point& p ) const
		{
			return _min.getX2D() <= p.getX2D() && _min.getY2D() <= p.getY2D() &&
			_max.getX2D() >= p.getX2D() && _max.getY2D() >= p.getY2D();
		}
		
		bool AABB::contains( const AABB& aabb ) const
		{
			return _min.getX2D() <= aabb.getMin().getX2D() &&
			_min.getY2D() <= aabb.getMin().getY2D() &&
			_max.getX2D() >= aabb.getMax().getX2D() &&
			_max.getY2D() >= aabb.getMax().getY2D();
		}
		
		bool AABB::intersects( const AABB& aabb ) const
		{
			if( _max.getX2D() < aabb._min.getX2D() )
				return false;
			
			if( _min.getX2D() > aabb._max.getX2D() )
				return false;
			
			if( _max.getY2D() < aabb._min.getY2D() )
				return false;
			
			if( _min.getY2D() > aabb._max.getY2D() )
				return false;
			
			return true;
		}
		
		AABB AABB::operator+(const Point moveBy) const
		{
			AABB ret;
			ret._min = this->_min + moveBy;
			ret._max = this->_max + moveBy;
			return ret;
		}
	}
}




