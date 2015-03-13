//
//  SpriteActionMoveBy.h
//  pxlframework
//
//  Created by Adrien Duermaël on 12/3/13.
//
//


#ifndef __pxlframework__SpriteActionMoveBy__
#define __pxlframework__SpriteActionMoveBy__


// pxlframework
#include "Action.h"
#include "Sprite.h"
#include "Point.h"


namespace px
{

	namespace engine
	{
    
	    class SpriteActionMoveBy : public Action
	    {
	        
	    public:
	        /**
	         * Factory method
	         * @param duration in second
	         * @param scale in percentage
	         */
	        static SpriteActionMoveBy* withDuration(const Tick::Duration duration, const Point delta);
	        
	        
	        /**
	         * Destructor
	         */
	        virtual ~SpriteActionMoveBy();
	        
	        /**
	         * Initialisation used by the factory method
	         * @param duration in second
	         * @param scale in percentage
	         * @return false if initialisation failed
	         */
	        bool init(const Tick::Duration duration, const Point delta);
	        
	        
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
	        SpriteActionMoveBy();
	        
	        /** Point at the begining of the action */
	        Point _origin;
	        
	        /** Delta to move by */
	        Point _by;
	        
	    private:
	        
	        /** We know the reciever IS a sprite, so we save a casted version in start */
	        Sprite *_receiver;
	        
	        /** Disable copying */
	        DISALLOW_COPY_AND_ASSIGN(SpriteActionMoveBy);
	        
	    };
    }
}


#endif




