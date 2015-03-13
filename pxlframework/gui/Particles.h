//
//  Particles.h
//  pxlframework
//
//  Created by Adrien Duermaël on 6/2/14.
//
//


#ifndef __pxlframework__Particles__
#define __pxlframework__Particles__


// C++
#include <string>
#include <vector>
#include <deque>
// pxlframework
#include "MenuSprite.h"


namespace px
{
	namespace engine
	{
		/**
		 * @todo we could override addChild and use instead addIcon and addLabel
		 */
		class Particles : public MenuSprite
		{
		public:
			
			/**
             * @param texture name
             * @param amount of particles generated per second
             * @param duration of the explosion (0.0 == infinite)
             * @param lifetime of a particle
             * @param particle speed (in points per second)
             * @param delay before starting particle
			 */
			static Particles* newParticles(const std::string& textureName,float nbPerSecond, Tick::Duration duration, float lifeTime, float speedMin, float speedMax, float delay);
			
			/**
             * To display different sizes of the same particle
             */
            void setScales(float scaleMin, float scaleMax){ _scaleMin = scaleMin; _scaleMax = scaleMax; }
            
            /**
             * To display different opacities for the same particle
             */
            inline void setOpacities(float opacityMin, float opacityMax){ _opacityMin = opacityMin; _opacityMax = opacityMax; }
            
            
            
			/**
			 * Destructor
			 */
			virtual ~Particles();
            
            
            /**
			 *
			 */
			virtual void tick(const Tick::Duration dt);
			
			
#pragma mark - Public Methods -
            
			
			
#pragma mark - Accessors -
			
			
			
#pragma mark - Modifiers -
			
			
			
#pragma mark - Inherited -
			
			
		protected:
			
			/**
			 * Default Constructor
			 */
			Particles(const std::string& textureName,float nbPerSecond, Tick::Duration duration, float lifeTime, float speedMin, float speedMax, float delay);
			
            bool init();
			
			
		private:
			
            float _nbPerSecond;
            float _duration;
            float _lifeTime;
            float _speedMin;
            float _speedMax;
            float _delay;
            std::string _textureName;
            
            float _scaleMin;
            float _scaleMax;
            
            float _opacityMin;
            float _opacityMax;
            
            Tick::Duration _next;
            Tick::Duration _last;
            Tick::Duration _totalDuration;
            
            std::deque<MenuSprite*> _particles;
            void flushParticles();
            
			/** Disable copying */
			DISALLOW_COPY_AND_ASSIGN(Particles);
		};
	}
}


#endif




