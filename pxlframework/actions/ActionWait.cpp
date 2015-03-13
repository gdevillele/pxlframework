//
//  ActionWait.cpp
//  pxlframework
//
//  Created by Adrien Duermaël on 12/3/13.
//
//


#include "ActionWait.h"


namespace px
{
	namespace engine
	{
		/* static */ ActionWait* ActionWait::withDuration(const Tick::Duration d)
		{
			ActionWait* action = new ActionWait();
			
			if( ! action->init(d))
			{
				delete action;
				action = nullptr;
			}
			
			return action;
		}
	}
}




