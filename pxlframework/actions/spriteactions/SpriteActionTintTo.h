//
//  SpriteActionTintTo.h
//  pxlframework
//
//  Created by Axel Guilmin on 12/6/13.
//
//


#ifndef __pxlframework__SpriteActionTintTo__
#define __pxlframework__SpriteActionTintTo__



// pxlframework
#include "Action.h"
#include "Sprite.h"


namespace px
{

	namespace engine
	{
    
	    class SpriteActionTintTo : public Action
	    {
	        
	    public:
	        /**
	         * Factory method
	         * @param duration in second
	         * @param scale in percentage
	         */
	        static SpriteActionTintTo* withDuration(const Tick::Duration duration, const Color scale);
	        
	        /**
	         * Destructor
	         */
	        virtual ~SpriteActionTintTo();
	        
	        /**
	         * Initialisation used by the factory method
	         * @param duration in second
	         * @param scale in percentage
	         * @return false if initialisation failed
	         */
	        bool init(const Tick::Duration duration, const Color scale);
	        
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
	        
	    protected:
	        /**
	         * Default constructor
	         */
	        SpriteActionTintTo();
	        
	        /**  */
	        Color _origin;
	        
	        /**  */
	        Color _to;
	        
	    private:
	        
	        /** We know the reciever IS a sprite, so we save a casted version in start */
	        Sprite *_receiver;
	        
	        /** Disable copying */
	        DISALLOW_COPY_AND_ASSIGN(SpriteActionTintTo);
	        
	    };
	}
}


#endif




