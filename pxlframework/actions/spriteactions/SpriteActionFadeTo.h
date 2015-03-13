//
//  SpriteActionFadeTo.h
//  pxlframework
//
//  Created by Adrien Duermaël on 12/3/13.
//
//


#ifndef __pxlframework__SpriteActionFadeTo__
#define __pxlframework__SpriteActionFadeTo__


// pxlframework
#include "Action.h"
#include "Sprite.h"


namespace px
{

	namespace engine
	{

	    /**
	     * Sprite Action : FadeTo
	     * will shange the opacity
	     * @author Axel Guilmin
	     */
	    class SpriteActionFadeTo : public Action
	    {
	        
	    public:
	        /**
	         * Factory method
	         * @param duration in second
	         * @param opacity in percentage
	         */
	        static SpriteActionFadeTo* withDuration(const Tick::Duration duration, const float opacity);
	        
	        /**
	         * Destructor
	         */
	        virtual ~SpriteActionFadeTo();
	        
	        /**
	         * Initialisation used by the factory method
	         * @param duration in second
	         * @param scale in percentage
	         * @return false if initialisation failed
	         */
	        bool init(const Tick::Duration duration, const float opacity);
	        
	        /**
	         * Start the scaling on the specified receiver
	         * @param receiver the WorldElement which receive the action
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
	         * @todo
	         */
	        virtual void pause() {/*todo*/};
	        
	    protected:
	        /**
	         * Default constructor
	         */
	        SpriteActionFadeTo();
	        
	        /** Opacity at the begining of the action */
	        float _origin;
	        
	        /** Opacity at the end of the action */
	        float _to;
	        
	    private:
	        
	        Sprite *_receiver;
	        
	        /** Disable copying */
	        DISALLOW_COPY_AND_ASSIGN(SpriteActionFadeTo);
	    };
	}
}


#endif




