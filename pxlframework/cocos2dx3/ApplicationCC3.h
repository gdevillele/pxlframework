//
//  ApplicationCC3.h
//  pxlframework
//
//  Created by Gaëtan de Villèle on 2/6/14.
//
//


#ifndef __pxlframework__ApplicationCC3__
#define __pxlframework__ApplicationCC3__


// pxlframework
#include "Application.h"


namespace px
{
	namespace engine
	{
		/**
		 Template specialization for ApplicationTpl
		 COCOS2D-X V3
		 
		 @see "ApplicationTpl"
		 */
		template<>
		class ApplicationTpl<sdk::COCOS2D3> : public cocos2d::Application
		{
			
		public:
			
			ApplicationTpl<sdk::COCOS2D3>();
			virtual ~ApplicationTpl<sdk::COCOS2D3>();
			
			void run();
			
			virtual bool applicationDidFinishLaunching();
			virtual void applicationDidEnterBackground();
			virtual void applicationWillEnterForeground();
			virtual void applicationDidReceiveMemoryWarning();
			virtual void applicationWillResignActive();
			virtual void applicationDidBecomeActive();
			
			virtual void pause();
			virtual void resume();
			
			virtual bool screenshot(std::string storagePath);
			
			void showFps(bool active);
			
			
			
		protected:
			
			virtual Scene* createMainScene() = 0;
			
			
			
		private:
			
			/**
			 *
			 */
			Scene* _mainScene;
			
			/**
			 * Disable copying 
			 */
			DISALLOW_COPY_AND_ASSIGN(ApplicationTpl<sdk::COCOS2D3>);
			
		};
	}
}


#endif




