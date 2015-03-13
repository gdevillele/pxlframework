//
//  ScrollViewActionUnlock.cpp
//  pxlframework
//
//  Created by Axel Guilmin on 4/29/14.
//
//


#include "ScrollViewActionUnlock.h"

// pxlframework
#include "ScrollView.h"
#include "Tick.h"


namespace px
{
	namespace engine
	{
		/*static*/ ScrollViewActionUnlock* ScrollViewActionUnlock::instantaneous()
		{
			ScrollViewActionUnlock* action = new ScrollViewActionUnlock();
			
			if( ! action->init(0.0f))
			{
				delete action;
				action = nullptr;
			}
			
			return action;
		}
        
        /*virtual*/ void ScrollViewActionUnlock::start(Action_Receiver *receiver)
        {
            Action::start(receiver);
            
            ScrollView *sv = static_cast<ScrollView*>(receiver);
            
            sv->acceptTouches();
        }
	}
}




