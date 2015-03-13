//
//  SpriteActionMoveTo.h
//  pxlframework
//
//  Created by Adrien Duermaël on 1/3/14.
//
//


#ifndef __pxlframework__SpriteActionMoveTo__
#define __pxlframework__SpriteActionMoveTo__


// pxlframework
#include "Action.h"
#include "Sprite.h"
#include "Point.h"


namespace px
{
	namespace engine
	{
		
		class SpriteActionMoveTo : public Action
		{
			
		public:
			/**
			 * Factory method
			 * @param duration in second
			 * @param to
			 */
			static SpriteActionMoveTo* withDuration(const Tick::Duration duration, const Point to);
			
			
			/**
			 * Destructor
			 */
			virtual ~SpriteActionMoveTo();
			
			/**
			 * Initialisation used by the factory method
			 * @param duration in second
			 * @param to
			 * @return false if initialisation failed
			 */
			bool init(const Tick::Duration duration, const Point to);
			
			
			virtual void start(Action_Receiver *receiver);
			
			/**
			 * called once per frame by step() method. time a value between 0 and 1
			 * @param time percentage of the action progression
			 * For example:
			 * - 0.0 means that the action just started
			 * - 0.5 means that the action is in the middle
			 * - 1.0 means that the action is over
			 */
			virtual void update(const Percentage time);
			
			/**
			 * Called when the game is paused
			 */
			virtual void pause() {};
			
			virtual void stop() {update(1.0f);}
			
		protected:
			/**
			 * Default constructor
			 */
			SpriteActionMoveTo();
			
			/** Point at the begining of the action */
			Point _origin;
			
			/** Delta to move by */
			Point _to;
			
		private:
			
			/** We know the reciever IS a sprite, so we save a casted version in start */
			Sprite *_receiver;
			
			/** Disable copying */
			DISALLOW_COPY_AND_ASSIGN(SpriteActionMoveTo);
			
		};
		
	}
}


#endif




