//
//  SpriteActionCropTo.h
//  pxlframework
//
//  Created by Axel Guilmin on 4/23/14.
//
//


#ifndef __pxlframework__SpriteActionCropTo__
#define __pxlframework__SpriteActionCropTo__


// pxlframework
#include "Action.h"
#include "Sprite.h"
#include "Rect.h"


namespace px
{
    namespace engine
    {
        
        /**
         * Sprite Actpion : Crop To
         * Update the TextureRect
         * @file SpriteActionCropTo.h
         * @author Axel Guilmin
         * @date 4/23/14.
         */
        class SpriteActionCropTo : public Action
        {
            
        public:
            /**
             * Factory method
             * @param duration in second
             * @param scale in percentage
             */
            static SpriteActionCropTo* withDuration(const Tick::Duration duration, const px::tools::Rect rect);
            
            /**
             * Destructor
             */
            virtual ~SpriteActionCropTo();
            
            /**
             * Initialisation used by the factory method
             * @param duration in second
             * @param scale in percentage
             * @return false if initialisation failed
             */
            bool init(const Tick::Duration duration, const px::tools::Rect rect);
            
            /**
             *
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
             */
            SpriteActionCropTo();
            
            /**  */
            px::tools::Rect _origin;
            
            /**  */
            px::tools::Rect _to;
            
        private:
            
            /** We know the reciever IS a sprite, so we save a casted version in start */
            Sprite *_receiver;
            
            /** Disable copying */
            DISALLOW_COPY_AND_ASSIGN(SpriteActionCropTo);
            
        };
    }
}


#endif




