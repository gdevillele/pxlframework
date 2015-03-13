//
//  SpriteActionCropTo.cpp
//  pxlframework
//
//  Created by Axel Guilmin on 4/23/14.
//
//


#include "SpriteActionCropTo.h"

// pxlframework
#include "SpriteActionCropTo.h"
#include "Sprite.h"


namespace px
{
    namespace engine
    {
        
        /*static*/ SpriteActionCropTo* SpriteActionCropTo::withDuration(const Tick::Duration duration, const px::tools::Rect rect)
        {
            SpriteActionCropTo* action = new SpriteActionCropTo();
            
            if( ! action->init(duration, rect))
            {
                delete action;
                action = NULL;
            }
            
            return action;
        }
        
        /*virtual*/ SpriteActionCropTo::~SpriteActionCropTo()
        {
        }
        
        bool SpriteActionCropTo::init(const Tick::Duration duration, const px::tools::Rect rect)
        {
            if(Action::init(duration))
            {
                _to = rect;
                return true;
            }
            
            return false;
        }
        
        /*virtual*/ void SpriteActionCropTo::start(Action_Receiver *receiver)
        {
            //PXL_ASSERT( dynamic_cast<Sprite*>(receiver) != nullptr );
            
            Action::start(receiver);
            _receiver = static_cast<Sprite*>(receiver);
            // @todo sprite may be NULL
            _origin = _receiver->getTextureRect();
        }
        
        /*virtual*/ void SpriteActionCropTo::update(const Percentage time)
        {
            px::tools::Rect newRect(
                             _origin.getX() * (1.0f - time) + _to.getX() * time,
                             _origin.getY() * (1.0f - time) + _to.getY() * time,
                             _origin.getWidth() * (1.0f - time) + _to.getWidth() * time,
                             _origin.getHeight() * (1.0f - time) + _to.getHeight() * time
                             );
            
            _receiver->setTextureRect(newRect);
        }
        
        SpriteActionCropTo::SpriteActionCropTo() : Action(),
        _origin(),
        _to(),
        _receiver(nullptr)
        {
            
        }
    }
}




