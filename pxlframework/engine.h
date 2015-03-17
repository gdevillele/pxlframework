//
//  engine.h
//  pxlframework
//
//  Created by Pablo Gonzalez on 10/31/13.
//
//


#ifndef __pxlframework__engine__
#define __pxlframework__engine__


//---------------------------------
// CHOOSE THE RENDERING LAYER HERE!
//---------------------------------
#define PXLFRAMEWORK_RENDERING_COCOS2D_V3 1
#define PXLFRAMEWORK_RENDERING_COCOS2D_V2 0
#define PXLFRAMEWORK_RENDERING_SPRITEKIT  0


namespace px
{
	namespace engine
	{
		/**
		 * list of available renderers
		 */
		enum sdk
		{
			COCOS2D3 = 1,
			COCOS2D = 2,
			SPRITEKIT = 3
		};
	}
}


// define the FWK macro
// TODO: check that only one is defined to 1 at a time
#undef FWK
#if   PXLFRAMEWORK_RENDERING_COCOS2D_V3 == 1 && PXLFRAMEWORK_RENDERING_COCOS2D_V2 == 0 && PXLFRAMEWORK_RENDERING_SPRITEKIT == 0
#define FWK px::engine::sdk::COCOS2D3
#elif PXLFRAMEWORK_RENDERING_COCOS2D_V3 == 0 && PXLFRAMEWORK_RENDERING_COCOS2D_V2 == 1 && PXLFRAMEWORK_RENDERING_SPRITEKIT == 0
#define FWK px::engine::sdk::COCOS2D
#elif PXLFRAMEWORK_RENDERING_COCOS2D_V3 == 0 && PXLFRAMEWORK_RENDERING_COCOS2D_V2 == 0 && PXLFRAMEWORK_RENDERING_SPRITEKIT == 1
#define FWK px::engine::sdk::SPRITEKIT
#else
#error Need PXLFRAMEWORK_RENDERING_COCOS2D_V3 or PXLFRAMEWORK_RENDERING_COCOS2D_V2 or PXLFRAMEWORK_RENDERING_SPRITEKIT to be defined to 1 (and the others to 0)
#endif


#ifdef __OBJC__
#define OBJC_CLASS(name) @class name
#else
#define OBJC_CLASS(name) typedef struct objc_object name
#endif


#endif




