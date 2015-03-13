//
//  ProgressBar.cpp
//  pxlframework
//
//  Created by Axel Guilmin on 1/17/14.
//
//


#include "ProgressBar.h"


namespace px
{
	namespace engine
	{
		
#pragma mark - Instance building functions -
		
		ProgressBar* ProgressBar::newProgressBar(const std::string& backgroundTextureName,
												 const std::string& leftTextureName,
												 const std::string& rightTextureName,
												 const RelativePosition relativePosition,
												 const RelativePosition anchor,
												 const Point& position,
												 const float percentage,
												 const float width)
		{
			ProgressBar* pb = new ProgressBar();
			
			if(! pb->init(backgroundTextureName, leftTextureName, rightTextureName, relativePosition, anchor, position, percentage, width))
			{
				delete pb;
				pb = nullptr;
			}
			
			return pb;
		}
		
		
#pragma mark - Constructor / Destructor -
		
		ProgressBar::ProgressBar() : MenuSprite(),
		_percentage(0.0f)
		{}
		
		/*virtual*/
		ProgressBar::~ProgressBar()
		{}
		
		
#pragma mark - Public Methods -
		
		
		
		
		
		
		
#pragma mark - Inherited Methods -
		
		
#pragma mark - Private Methods -
		
		bool ProgressBar::init(const std::string& backgroundTextureName,
							   const std::string& leftTextureName,
							   const std::string& rightTextureName,
							   const RelativePosition relativePosition,
							   const RelativePosition anchor,
							   const Point& position,
							   const float percentage,
							   const float width)
		{
			
			// define MenuSprite specific attributes
			setTextureName(backgroundTextureName);
			setRelativePosition(relativePosition);
			setAnchor(MenuSprite::convertRelativePositionIntoAnchorPoint(anchor));
			setPosition(Point(position.getX2D(), position.getY2D()));
			
			// define ProgressBar specific attributes
			
			// store the width (we need it and we don't have it
			// because the renderer instance has not been created yet)
			setContentSize(Size(width, 0.0f));
			
			_left = MenuSprite::newMenuSpriteWithTexture(leftTextureName,
														 MenuSprite::RelativePosition::LEFT,
														 MenuSprite::RelativePosition::LEFT,
														 Point(0.0f, 0.0f));
			
			addChild(_left);
			
			
			_right = MenuSprite::newMenuSpriteWithTexture(rightTextureName,
														  MenuSprite::RelativePosition::RIGHT,
														  MenuSprite::RelativePosition::RIGHT,
														  Point(0.0f, 0.0f));
			
			addChild(_right);
			
			setPercentage(percentage);
			
			return _left && _right;
		}
		
		
		
		void ProgressBar::setPercentage(const float percentage)
		{
			_percentage = std::max(0.000f, std::min(1.000f, percentage));
			
            px::tools::Rect r = px::tools::Rect(1.0f - _percentage, 0.0f, _percentage, 1.0f);
            
            _right->setTextureRect(r);
            
            _right->setPosition({ -(1.0f - _percentage) * getContentSize().getWidth(),0.0f});
            
            px::tools::Rect l = px::tools::Rect(0.0f, 0.0f, _percentage, 1.0f);
            
            _left->setTextureRect(l);
		}
	}
}




