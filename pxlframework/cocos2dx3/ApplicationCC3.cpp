//
//  ApplicationCC3.cpp
//  pxlframework
//
//  Created by Gaëtan de Villèle on 2/6/14.
//
//


#include "ApplicationCC3.h"


// pxlframework
#include "utils.h"


namespace px
{
	namespace engine
	{
		//--------------------------------------------------------------------------------
		ApplicationTpl<sdk::COCOS2D3>::ApplicationTpl() : cocos2d::Application(),
		_mainScene(nullptr)
		{}
		
		
		
		//--------------------------------------------------------------------------------
		/*virtual*/
		ApplicationTpl<sdk::COCOS2D3>::~ApplicationTpl()
		{}
		
		
		
		//--------------------------------------------------------------------------------
		void ApplicationTpl<sdk::COCOS2D3>::run()
		{
			cocos2d::Application::getInstance()->run();
		}
		
		
		
		//--------------------------------------------------------------------------------
		bool ApplicationTpl<sdk::COCOS2D3>::applicationDidFinishLaunching()
		{
			PXLLOG("GAETAN - ApplicationTpl<sdk::COCOS2D3>::applicationDidFinishLaunching\n");
			
			// set FPS. the default value is 1.0/60 if you don't call this
			cocos2d::Director::getInstance()->setAnimationInterval(1.0/60.0);
			
			_mainScene = createMainScene();
			
			// run
			cocos2d::Director::getInstance()->runWithScene(_mainScene);
			
			return true;
		}
		
		
		
		//--------------------------------------------------------------------------------
		void ApplicationTpl<sdk::COCOS2D3>::applicationDidEnterBackground()
		{
			PXLLOG("GAETAN - ApplicationTpl<sdk::COCOS2D3>::applicationDidEnterBackground\n");
            cocos2d::Director::getInstance()->stopAnimation();
            cocos2d::Director::getInstance()->pause();
		}
		
		
		
		//--------------------------------------------------------------------------------
		void ApplicationTpl<sdk::COCOS2D3>::applicationWillResignActive()
		{
			PXLLOG("GAETAN - ApplicationTpl<sdk::COCOS2D3>::applicationWillResignActive\n");
			cocos2d::Director::getInstance()->stopAnimation();
			cocos2d::Director::getInstance()->pause();
		}
		
		
		
		void ApplicationTpl<sdk::COCOS2D3>::applicationDidBecomeActive()
		{
			PXLLOG("GAETAN - ApplicationTpl<sdk::COCOS2D3>::applicationDidBecomeActive\n");
			cocos2d::Director::getInstance()->startAnimation();
			cocos2d::Director::getInstance()->resume();
		}
		
		
		
		//--------------------------------------------------------------------------------
		void ApplicationTpl<sdk::COCOS2D3>::applicationWillEnterForeground()
		{
			PXLLOG("GAETAN - ApplicationTpl<sdk::COCOS2D3>::applicationWillEnterForeground\n");
            cocos2d::Director::getInstance()->startAnimation();
            cocos2d::Director::getInstance()->resume();
            
			// if you use SimpleAudioEngine, it must resume here
			// SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
		}
		
		
		
		//--------------------------------------------------------------------------------
		void ApplicationTpl<sdk::COCOS2D3>::applicationDidReceiveMemoryWarning()
		{
			PXLLOG("ApplicationTpl<sdk::COCOS2D3>::applicationDidReceiveMemoryWarning\n");
			cocos2d::Director::getInstance()->purgeCachedData();
		}
		
		
		
		//--------------------------------------------------------------------------------
		void ApplicationTpl<sdk::COCOS2D3>::pause()
		{
			PXLLOG("GAETAN - ApplicationTpl<sdk::COCOS2D3>::pause\n");
			cocos2d::Director::getInstance()->pause();
		}
		
		
		
		//--------------------------------------------------------------------------------
		void ApplicationTpl<sdk::COCOS2D3>::resume()
		{
			PXLLOG("GAETAN - ApplicationTpl<sdk::COCOS2D3>::resume\n");
			cocos2d::Director::getInstance()->resume();
		}
		
		
		
		//--------------------------------------------------------------------------------
        /*
         Ad: I took that code from utils::captureScreen() introduced in Cocos2D-X v3.2 alpha0
         */
		bool ApplicationTpl<sdk::COCOS2D3>::screenshot(std::string storagePath)
		{
            
            cocos2d::GLView* glView = cocos2d::Director::getInstance()->getOpenGLView();
            cocos2d::Size frameSize = glView->getFrameSize();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
            frameSize = frameSize * glView->getFrameZoomFactor() * glView->getRetinaFactor();
#endif
            
            int width = static_cast<int>(frameSize.width);
            int height = static_cast<int>(frameSize.height);
            
            std::string outputFile = "";
            
            do
            {
                std::shared_ptr<GLubyte> buffer(new GLubyte[width * height * 4], [](GLubyte* p){ CC_SAFE_DELETE_ARRAY(p); });
                if (!buffer)
                {
                    break;
                }
                
                glPixelStorei(GL_PACK_ALIGNMENT, 1);
                
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
                // The frame buffer is always created with portrait orientation on WP8.
                // So if the current device orientation is landscape, we need to rotate the frame buffer.
                auto renderTargetSize = glView->getRenerTargetSize();
                CCASSERT(width * height == static_cast<int>(renderTargetSize.width * renderTargetSize.height), "The frame size is not matched");
                glReadPixels(0, 0, (int)renderTargetSize.width, (int)renderTargetSize.height, GL_RGBA, GL_UNSIGNED_BYTE, buffer.get());
#else
                glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, buffer.get());
#endif
                
                std::shared_ptr<GLubyte> flippedBuffer(new GLubyte[width * height * 4], [](GLubyte* p) { CC_SAFE_DELETE_ARRAY(p); });
                if (!flippedBuffer)
                {
                    break;
                }
                
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
                if (width == static_cast<int>(renderTargetSize.width))
                {
                    // The current device orientation is portrait.
                    for (int row = 0; row < height; ++row)
                    {
                        memcpy(flippedBuffer.get() + (height - row - 1) * width * 4, buffer.get() + row * width * 4, width * 4);
                    }
                }
                else
                {
                    // The current device orientation is landscape.
                    for (int row = 0; row < width; ++row)
                    {
                        for (int col = 0; col < height; ++col)
                        {
                            *(int*)(flippedBuffer.get() + (height - col - 1) * width * 4 + row * 4) = *(int*)(buffer.get() + row * height * 4 + col * 4);
                        }
                    }
                }
#else
                for (int row = 0; row < height; ++row)
                {
                    memcpy(flippedBuffer.get() + (height - row - 1) * width * 4, buffer.get() + row * width * 4, width * 4);
                }
#endif
                
                std::shared_ptr<cocos2d::Image> image(new cocos2d::Image);
                
                if (image)
                {
                    image->initWithRawData(flippedBuffer.get(), width * height * 4, width, height, 8);
                    
                    
                    if (image->saveToFile(storagePath.c_str(),false))
                    {
                        return true;
                    }
                    else
                    {
                        return false;
                    }
                }
            } while(0);
            
            return false;
		}
		
		
		
		//--------------------------------------------------------------------------------
		void ApplicationTpl<sdk::COCOS2D3>::showFps(bool active)
		{
			cocos2d::Director::getInstance()->setDisplayStats(active);
		}
		
		//--------------------------------------------------------------------------------
	}
}




