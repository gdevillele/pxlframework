//
//  Particles.cpp
//  pxlframework
//
//  Created by Adrien Duermaël on 6/2/14.
//
//


#include "Particles.h"

// pxlframework
#include "actions.h"


namespace px
{
	namespace engine
	{
        /*static*/ Particles* Particles::newParticles(const std::string& textureName,float nbPerSecond, float duration, float lifeTime, float speedMin, float speedMax, float delay)
        {
            Particles* result = new Particles(textureName,nbPerSecond, duration, lifeTime, speedMin,speedMax, delay);
            
            if (!result->init())
            {
                delete result;
                result = nullptr;
            }
            
            return result;
        }
        
        
        bool Particles::init()
        {
            return MenuSprite::init({0.0f,0.0f}, MenuSprite::RelativePosition::CENTER, MenuSprite::RelativePosition::CENTER, {0,0});
        }
        
        
        Particles::Particles(const std::string& textureName,float nbPerSecond, float duration, float lifeTime, float speedMin, float speedMax, float delay) : MenuSprite::MenuSprite(),
        _nbPerSecond(nbPerSecond),
        _lifeTime(lifeTime),
        _speedMin(speedMin),
        _speedMax(speedMax),
        _delay(delay),
        _last(0.0f),
        _totalDuration(0.0f),
        _textureName(textureName),
        _scaleMin(1.0f),
        _scaleMax(1.0f),
        _opacityMin(1.0f),
        _opacityMax(1.0f),
        _duration(duration)
        {
            _next = 1.0f / _nbPerSecond;
        }
        
        Particles::~Particles()
        {
            
        }
        
        /*virtual*/ void Particles::tick(const Tick::Duration dt)
        {
            _totalDuration += dt;
            
            if (_totalDuration >= _delay && ((_totalDuration <= _duration + _delay) || (_duration == 0.0f)))
            {
                _last += dt;
                
                if (_last >= _next)
                {
                    //_next = 1.0f / _nbPerSecond - (_last - _next);
                    _next = 1.0f / _nbPerSecond;
                    _last = 0.0f;
                    
                    float speed = _speedMin + (_speedMax - _speedMin) * (float)(rand() % 100) * 0.01f;
                    
                    Point delta = Point(Point::createWithPolar(speed * _lifeTime, rand()%360 * DEG_TO_RAD));
                    
                    MenuSprite* particle = MenuSprite::newMenuSpriteWithTexture(_textureName, MenuSprite::RelativePosition::CENTER , MenuSprite::RelativePosition::CENTER, {0,0});
                    
                    particle->setOpacity(0.0f);
                    particle->setScale(_scaleMin + (_scaleMax - _scaleMin) * (float)(rand() % 100) * 0.01f);
                    
                    particle->setRotation(rand()%360 * DEG_TO_RAD);
                    
                    particle->runAction(SpriteActionMoveBy::withDuration(_lifeTime,delta));
                    
                    float desiredOpacity = _opacityMin + (_opacityMax - _opacityMin) * (float)(rand() % 100) * 0.01f;
                    
                    particle->runAction(ActionSequence::withActions(
                                                                    SpriteActionFadeTo::withDuration(_lifeTime * 0.05f, desiredOpacity),
                                                                    ActionWait::withDuration(_lifeTime * 0.80f),
                                                                    SpriteActionFadeTo::withDuration(_lifeTime * 0.15f, 0.0f)
                                                                    ));
                    
                    _particles.push_back(particle);
                    
                    addChild(particle);
                }
            }
            
            flushParticles();
            Sprite::tick(dt);
        }
        
        
        void Particles::flushParticles()
        {
            if (!_particles.empty())
            {
                if(_particles.front()->countActions() == 0)
                {
                    removeChild(_particles.front());
                    _particles.pop_front();
                }
            }
        }
    }
}




