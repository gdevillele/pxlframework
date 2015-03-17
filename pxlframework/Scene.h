//
//  Scene.h
//  pxlframework
//
//  Created by Pablo Gonzalez on 10/31/13.
//
//


#ifndef __pxlframework__Scene__
#define __pxlframework__Scene__


#include "engine.h"


namespace px
{
	namespace engine
	{		
		template<sdk>
		class SceneTpl
		{
			
		public:
			
			/**
			 @brief  The function is called when the scene becomes active
			 */
			virtual void onEnter();
			
			/**
			 @brief  The function is called when the scene exits
			 */
			virtual void onExit();
			
			/**
			 * tick function here ???
			 */
			
			// TODO: GAETAN: is it really necessary ??
			// what is this size thing ?
			//void setSize(Size size);
			//Size getSize() const;
			
		};
		
		typedef SceneTpl<FWK> Scene;
	}
}


// Add specializations here
#if PXLFRAMEWORK_RENDERING_COCOS2D_V3 == 1
    #include "cocos2dx3/SceneCC3.h"
#elif PXLFRAMEWORK_RENDERING_COCOS2D_V2 == 1
    #include "cocos2dx2/SceneCC2.h"
#elif PXLFRAMEWORK_RENDERING_SPRITEKIT == 1
    #include "spritekit/SceneSK.h"
#endif


#endif




