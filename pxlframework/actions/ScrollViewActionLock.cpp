//
//  ScrollViewActionLock.cpp
//  pxlframework
//
//  Created by Axel Guilmin on 4/29/14.
//
//


#include "ScrollViewActionLock.h"

// pxlframework
#include "ScrollView.h"
#include "Tick.h"


namespace px
{
	namespace engine
	{
		/*static*/ ScrollViewActionLock* ScrollViewActionLock::instantaneous()
		{
			ScrollViewActionLock* action = new ScrollViewActionLock();
			
			if( ! action->init(0.0f))
			{
				delete action;
				action = nullptr;
			}
			
			return action;
		}
        
        /*virtual*/ void ScrollViewActionLock::start(Action_Receiver *receiver)
        {
            Action::start(receiver);
            
            ScrollView *sv = static_cast<ScrollView*>(receiver);
            
            sv->ignoreTouches();
        }
	}
}




