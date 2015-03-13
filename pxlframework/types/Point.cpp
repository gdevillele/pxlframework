//
//  Point.cpp
//  pxlframework
//
//  Created by Adrien Duermaël on 8/12/13.
//
//


#include "Point.h"

// C++
#include <sstream>
#include <cmath>
// pxlframework
#include "utils.h"
#include "StringUtils.h"


namespace px
{
	namespace engine
	{
		
#pragma mark - Constructor / Destructor -
		
		Point::Point() :
		_x(0.0f),
		_y(0.0f)
		{}
		
		
		
		Point::Point(const float x, const float y) :
		_x(x),
		_y(y)
		{
			// for dev/debug purpose, to detect NaN value
			PXL_ASSERT(_x == _x);
			PXL_ASSERT(_y == _y);
		};
		
		
		
		Point::Point(Point& other) :
		_x(other._x),
		_y(other._y)
		{
			// for dev/debug purpose, to detect NaN value
			PXL_ASSERT(_x == _x);
			PXL_ASSERT(_y == _y);
		}
		
		
		
		Point::Point(const Point& other) :
		_x(other._x),
		_y(other._y)
		{
			// for dev/debug purpose, to detect NaN value
			PXL_ASSERT(_x == _x);
			PXL_ASSERT(_y == _y);
		}
		
		
		
		Point::~Point()
		{}
		
		
		
#pragma mark - Public Methods -
		
		float Point::distanceWith( const float x, const float y ) const
		{
			PXL_ASSERT( distanceSquaredWith( x, y ) >= 0.0f);
			
			return sqrt( distanceSquaredWith( x, y ) );
		}
		
		
		
		float Point::distanceWith( const Point p ) const
		{
			PXL_ASSERT( distanceSquaredWith( p._x, p._y) >= 0.0f);
			
			return sqrt( distanceSquaredWith( p._x, p._y) );
		}
		
		
		
		float Point::distanceSquaredWith( const float x, const float y ) const
		{
			PXL_ASSERT(x == x);
			PXL_ASSERT(y == y);
			
			const float dx = x - _x;
			const float dy = y - _y;
			return (dx * dx + dy * dy);
		}
		
		
		
		float Point::distanceSquaredWith( const Point p ) const
		{
			PXL_ASSERT(p._x == p._x);
			PXL_ASSERT(p._y == p._y);
			
			const float dx = p._x - _x;
			const float dy = p._y - _y;
			return (dx * dx + dy * dy);
		}
		
		
		
		float Point::distanceWithOrigin() const
		{
			return std::sqrt( (_x * _x) + (_y * _y) );
		}
		
		
		
#pragma mark - Modifiers -
		
		
		void Point::setX2D( const float x )
		{
			PXL_ASSERT(x == x);
			_x = x;
		}
		
		void Point::setY2D( const float y )
		{
			PXL_ASSERT(y == y);
			_y = y;
		}
		
		void Point::set2D( const float x, const float y)
		{
			PXL_ASSERT(x == x);
			PXL_ASSERT(y == y);
			_x = x;
			_y = y;
		}
		
		void Point::addX2D( const float x )
		{
			PXL_ASSERT(x == x);
			_x += x;
		}
		
		void Point::addY2D( const float y )
		{
			PXL_ASSERT(y == y);
			_y += y;
		}
		
		void Point::add2D( const float x, const float y )
		{
			PXL_ASSERT(x == x);
			PXL_ASSERT(y == y);
			_x += x;
			_y += y;
		}
		
		void Point::set(const Point& point)
		{
			set2D(point.getX2D(), point.getY2D());
		}

		
		

		
		
		
#pragma mark - Operators -
		
		Point Point::operator+(const Point& v) const
		{
			PXL_ASSERT(v._x == v._x);
			PXL_ASSERT(v._y == v._y);
			
			return Point(_x + v._x, _y + v._y);
		}
		
		Point Point::operator-(const Point& v) const
		{
			PXL_ASSERT(v._x == v._x);
			PXL_ASSERT(v._y == v._y);
			
			return Point(_x - v._x, _y - v._y);
		}
		
		void Point::operator+=(const Point& v)
		{
			PXL_ASSERT(v._x == v._x);
			PXL_ASSERT(v._y == v._y);
			
			(*this)._x += v._x;
			(*this)._y += v._y;
		}
		void Point::operator-=(const Point& v)
		{
			PXL_ASSERT(v._x == v._x);
			PXL_ASSERT(v._y == v._y);
			
			(*this)._x -= v._x;
			(*this)._y -= v._y;
		}
		
		Point Point::operator/(float s) const
		{
			PXL_ASSERT(s != 0.0f);
			PXL_ASSERT(s == s);
			PXL_ASSERT(1.0f / s == 1.0f / s);
			
			return Point(_x / s, _y / s);
		}
		
		Point Point::operator*(float s) const
		{
			PXL_ASSERT(s == s);
			
			return Point(_x * s, _y * s);
		}
		
		void Point::operator/=(float s)
		{
			PXL_ASSERT(s != 0.0f);
			PXL_ASSERT(s == s);
			PXL_ASSERT(1.0f / s == 1.0f / s);
			
			(*this)._x /= s;
			(*this)._y /= s;
		}
		
		void Point::operator*=(float s)
		{
			PXL_ASSERT(s == s);
			
			(*this)._x *= s;
			(*this)._y *= s;
		}
		
		bool Point::operator== (const Point &v)const
		{
			return _x == v._x && _y == v._y ;
		}
		
		Point& Point::operator=(const Point& other)
		{
			PXL_ASSERT(other._x == other._x);
			PXL_ASSERT(other._y == other._y);
			_x = other._x;
			_y = other._y;
			return *this;
		}
		
		inline Point::operator std::string() const
		{
            return "Point : #1 #2"_format( _x, _y );
		}
	}
}




