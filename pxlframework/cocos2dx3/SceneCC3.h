//
//  SceneCC3.h
//  pxlframework
//
//  Created by Gaëtan de Villèle on 2/6/14.
//
//


#ifndef __pxlframework__SceneCC3__
#define __pxlframework__SceneCC3__


// pxlframework
#include "engine.h"
#include "Scene.h"
// cocos2dx v3
#include <cocos2d.h>


namespace px
{
	namespace engine
	{
		class MasterCC3;
		
		template <>
		class SceneTpl<sdk::COCOS2D3> : public cocos2d::Scene
		{
			
		public:
			
			/**
			 * factory method
			 */
			static SceneTpl<sdk::COCOS2D3>* create();
			
			/**
			 * destructor
			 */
			virtual ~SceneTpl<sdk::COCOS2D3>();
			
			/**
			 * init
			 */
			virtual bool init();
			
			/**
			 @brief  The function is called when the scene becomes active
			 */
			virtual void onEnter();
			
			/**
			 @brief  The function is called when the scene exits
			 */
			virtual void onExit();
			
			/**
			 * tick method
			 */
			virtual void tick(const float dt);
			
			
		protected:
			
			/**
			 * default constructor
			 */
			SceneTpl<sdk::COCOS2D3>();
			
			
		private:
			
			/** Disable copying */
			DISALLOW_COPY_AND_ASSIGN(SceneTpl<sdk::COCOS2D3>);
		};
	}
}


#endif




