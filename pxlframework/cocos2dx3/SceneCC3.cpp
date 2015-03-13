//
//  SceneCC3.cpp
//  pxlframework
//
//  Created by Gaëtan de Villèle on 2/6/14.
//
//


#include "SceneCC3.h"


namespace px
{
	namespace engine
	{
		
#pragma mark - static -
		
		SceneTpl<sdk::COCOS2D3>* SceneTpl<sdk::COCOS2D3>::create()
		{
			SceneTpl<sdk::COCOS2D3>* result = new SceneTpl<sdk::COCOS2D3>();
			if (result->init() == false)
			{
				delete result;
				result = nullptr;
			}
			return result;
		}
		
		
		
#pragma mark - constructor & destructor -
		
		SceneTpl<sdk::COCOS2D3>::SceneTpl()
		{}
		
		
		
		SceneTpl<sdk::COCOS2D3>::~SceneTpl()
		{}
		
		
		
#pragma mark - public methods -
		
		/**
		 * init
		 */
		bool SceneTpl<sdk::COCOS2D3>::init()
		{
			this->autorelease();
			return true;
		}
		
		
		/**
		 @brief  The function is called when the scene becomes active
		 */
		void SceneTpl<sdk::COCOS2D3>::onEnter()
		{
			schedule(schedule_selector(SceneTpl<sdk::COCOS2D3>::tick));
			cocos2d::Scene::onEnter();
		}
		
		
		
		/**
		 @brief  The function is called when the scene exits
		 */
		void SceneTpl<sdk::COCOS2D3>::onExit()
		{
			unschedule(schedule_selector(SceneTpl<sdk::COCOS2D3>::tick));
			cocos2d::Scene::onExit();
		}
		
		
		
		void SceneTpl<sdk::COCOS2D3>::tick(const float dt)
		{}
	}
}




