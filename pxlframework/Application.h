//
//  Application.h
//  pxlframework
//
//  Created by Pablo Gonzalez on 10/31/13.
//
//


#ifndef __pxlframework__Application__
#define __pxlframework__Application__


// engine
#include "engine.h"
#include "Scene.h"


//OBJC_CLASS(UIView);


namespace px
{
	namespace engine
	{
		template<sdk>
		class ApplicationTpl
		{
			
		public:
			
			/**
			 Construct application with window
			 @param window Application's main window
			 */
			ApplicationTpl();
			
			/**
			 Destructor
			 */
			virtual ~ApplicationTpl();
			
			/**
			 Run the application
			 */
			void run();
			
			/**
			 @brief    Implement init code here.
			 @return true    Initialize success, app continue.
			 @return false   Initialize failed, app terminate.
			 */
			virtual bool applicationDidFinishLaunching();
			
			/**
			 @brief  The function is called when the application enters the background
			 */
			virtual void applicationDidEnterBackground();
			
			/**
			 @brief  The function is called when the application enters the foreground
			 */
			virtual void applicationWillEnterForeground();
			
			/**
			 @brief  The function is called when the application receives a memory warning
			 */
			virtual void applicationDidReceiveMemoryWarning();
			
			/**
			 Pause application
			 */
			virtual void pause();
			
			/**
			 Resume application from pause
			 */
			virtual void resume();
			
			/**
			 *
			 */
			virtual bool screenshot(std::string storagePath);
			
			/**
			 * 
			 */
			void showFps(bool active);
			
//			UIView* getView();
			
			
		protected:
			
			/**
			 *
			 */
			virtual Scene* createMainScene() = 0;
			
			/**
			 * disable copy
			 */
			DISALLOW_COPY_AND_ASSIGN(ApplicationTpl);
		};
		
		
		
		/**
		 * Create the type "Application" the game application will inherit from.
		 * This way, we are hidding the details about the rendering engine used.
		 */
		typedef ApplicationTpl<FWK> Application;
	}
}


// Add specializations here
#if PX_COCOS2D_V3 == 1
    #include "cocos2dx3/ApplicationCC3.h"
#elif PX_COCOS2D_V2 == 1
    #include "cocos2dx2/ApplicationCC2.h"
#elif PX_SPRITEKIT == 1
    #include "spritekit/ApplicationSK.h"
#endif


#endif




