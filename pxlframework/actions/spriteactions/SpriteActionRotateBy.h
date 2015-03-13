//
//  SpriteActionRotateBy.h
//  pxlframework
//
//  Created by Axel Guilmin on 12/2/13.
//
//


#ifndef __pxlframework__SpriteActionRotateBy__
#define __pxlframework__SpriteActionRotateBy__


// pxlframework
#include "Action.h"
#include "Sprite.h"


namespace px
{

	namespace engine
	{
    
	    /**
	     * Sprite Action : RotateBy
	     * will appy a rotation of the given angle, regardless the original angle
	     * @author Axel Guilmin
	     */
	    class SpriteActionRotateBy : public Action
	    {
	        
	    public:
	        /**
	         * Factory method
	         * @param duration in second
	         * @param angle in radian
	         */
	        static SpriteActionRotateBy* withDuration(const Tick::Duration duration, const Sprite::Angle angle);
	        
	        /**
	         * Destructor
	         * @todo stop the action properly
	         */
	        virtual ~SpriteActionRotateBy();
	        
	        /**
	         * Initialisation used by the factory method
	         * @param duration in second
	         * @param angle in radian
	         * @return false if initialisation failed
	         */
	        bool init(const Tick::Duration duration, const Sprite::Angle angle);
	        
	        /**
	         * Start the rotation on the specified receiver
	         * @param receiver the Sprite which receive the action
	         */
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
	         * empty
	         */
	        SpriteActionRotateBy();
	        
	        /** Angle of the receiver when the action started */
	        Sprite::Angle _origin;
	        
	        /** Angle to move by */
	        Sprite::Angle _by;
	        
	    private:
	        
	        /** We know the reciever IS a sprite so we save a casted version in start */
	        Sprite *_receiver;
	        
	        /** Disable copying */
	        DISALLOW_COPY_AND_ASSIGN(SpriteActionRotateBy);
	        
	    };
	}
}


#endif




