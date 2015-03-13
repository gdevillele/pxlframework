//
//  Sparkle.h
//  pxlframework
//
//  Created by Adrien Duermaël on 5/31/14.
//
//


#ifndef __pxlframework__Sparkle__
#define __pxlframework__Sparkle__


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
		class Sparkle : public MenuSprite
		{
		public:
			
			/**
             *
			 */
			static Sparkle* newSparkle(const std::string& textureName,float maxTime, float lifeTime, float delay);
			
			
			/**
			 * Destructor
			 */
			virtual ~Sparkle();
            
            
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
			Sparkle(const std::string& textureName,float maxTime, float lifeTime, float delay);
			
            bool init();
			
			
		private:
			
            float _maxTime;
            float _nextTime;
            float _lifeTime;
            std::string _textureName;
            Tick::Duration _lastSparkle;
            
            std::deque<MenuSprite*> _sparkles;
			
            
            void flushSparkles();
            
			/** Disable copying */
			DISALLOW_COPY_AND_ASSIGN(Sparkle);
		};
	}
}


#endif




