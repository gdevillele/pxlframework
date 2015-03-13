//
//  Sparkle.cpp
//  pxlframework
//
//  Created by Adrien Duermaël on 5/31/14.
//
//


#include "Sparkle.h"

// pxlframework
#include "actions.h"


namespace px
{
	namespace engine
	{
        Sparkle* Sparkle::newSparkle(const std::string& textureName,float maxTime, float lifeTime, float delay)
        {
            Sparkle* result = new Sparkle(textureName,maxTime,lifeTime, delay);
            
            if (!result->init())
            {
                delete result;
                result = nullptr;
            }
            
            return result;
        }
        
        
        bool Sparkle::init()
        {
            return MenuSprite::init({0.0f,0.0f}, MenuSprite::RelativePosition::CENTER, MenuSprite::RelativePosition::CENTER, {0,0});
        }
        
        
        Sparkle::Sparkle(const std::string& textureName,float maxTime, float lifeTime, float delay) : MenuSprite::MenuSprite(),
        _textureName(textureName),
        _maxTime(maxTime),
        _lifeTime(lifeTime),
        _lastSparkle(0.0f)
        {
            _nextTime = _maxTime / ((float)(rand() % 5) + 1) + delay;
        }
        
        Sparkle::~Sparkle()
        {
            
        }
        
        /*virtual*/ void Sparkle::tick(const Tick::Duration dt)
        {
            _lastSparkle += dt;
            
            if (_lastSparkle >= _nextTime)
            {
                _nextTime = _maxTime / ((float)(rand() % 5) + 1);
                _lastSparkle = 0;
                
                if (getParent() && getParent()->getContentSize().getHeight() > 0 && getParent()->getContentSize().getWidth() > 0)
                {
                    float w = (int)getParent()->getContentSize().getWidth();
                    float h = (int)getParent()->getContentSize().getHeight();
                    
                    float x = rand() % (int)w;
                    float y = rand() % (int)h;
                    
                    
                    MenuSprite* sparkle = MenuSprite::newMenuSpriteWithTexture(_textureName, MenuSprite::RelativePosition::CENTER , MenuSprite::RelativePosition::CENTER, {x - w * 0.5f , y - h * 0.5f});
                    
                    sparkle->setRotation(rand()%360 * DEG_TO_RAD);
                    sparkle->setScale(0.0f);
                    sparkle->runAction(ActionSequence::withActions(
                                                                   SpriteActionScaleTo::withDuration(_lifeTime * 0.3f, 1.0f),
                                                                   SpriteActionScaleTo::withDuration(_lifeTime * 0.7f, 0.0f)
                                                                   ));
                    
                    
                    _sparkles.push_back(sparkle);
                    
                    addChild(sparkle);
                }
            }
            
            flushSparkles();
            
            Sprite::tick(dt);
        }
        
        
        void Sparkle::flushSparkles()
        {
            if (!_sparkles.empty())
            {
                if(_sparkles.front()->countActions() == 0)
                {
                    removeChild(_sparkles.front());
                    _sparkles.pop_front();
                }
            }
        }
        
    }
}




