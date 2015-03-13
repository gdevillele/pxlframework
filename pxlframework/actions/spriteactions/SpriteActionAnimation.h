//
//  SpriteActionAnimation.h
//  pxlframework
//
//  Created by Adrien Duermaël on 5/28/14.
//
//


#ifndef __pxlframework__SpriteActionAnimation__
#define __pxlframework__SpriteActionAnimation__


// C++
#include <vector>
#include <cstdint>
#include <cstdarg>
// pxlframework
#include "Action.h"


namespace px
{
	namespace engine
	{
        class Sprite;
    
		/**
		 * Sprite Action : Animation
		 * Perfom an keyframe animation on the first sprite of a WorldElement
		 * @author Adrien Duermaël
		 */
		class SpriteActionAnimation : public Action
		{
		public:
			/**
			 * Factory method
			 * @param duration total duration of the animation
			 * @param frame first frame to display
			 * @param ... next frames, ordering by apparition
			 */
			// Can't implement it on the .cpp file because it's templated
			template <class ...T> static SpriteActionAnimation* withDurationAndFrames(const Tick::Duration duration, T... frames)
			{
				SpriteActionAnimation* action = new SpriteActionAnimation();
				
				uint8_t framesArray[sizeof...(frames)] = {static_cast<uint8_t>(frames)...};
				
				if( ! action->init(duration, sizeof...(frames), framesArray))
				{
					delete action;
					action = nullptr;
				}
				
				return action;
			};
			
			/**
			 * Factory method
			 * @param fps
			 * @param frame first frame to display
			 * @param ... next frames, ordering by apparition
			 */
			// Can't implement it on the .cpp file because it's templated
			template <class ...T> static SpriteActionAnimation* withFPSAndFrames(const uint8_t fps, T... frames)
			{
				SpriteActionAnimation* action = new SpriteActionAnimation();
				
				size_t frameCount = sizeof...(frames);
				uint8_t framesArray[frameCount] = {static_cast<uint8_t>(frames)...};
				const Tick::Duration duration = fps * frameCount;
				
				if( ! action->init(duration, frameCount, framesArray))
				{
					delete action;
					action = nullptr;
				}
				
			};
			
			/**
			 * Factory method - Use all frames aviables
			 * @param duration total duration of the animation
			 */
			static SpriteActionAnimation* withDuration(const Tick::Duration duration);
			
			/**
			 * Factory method - Use all frames aviables
			 * @param fps
			 * @todo withFPS isn't supported yet because we don't the amount of frame
			 */
			//static  WorldElementActionAnimation* withFPS(const uint8_t fps);
			
			/**
			 * Initialisation used by the factory method
			 * @param duration in second
			 * @param frameCount amout of frame in the frames array
			 * @param frames all frames by order of apparition, example "1,2,3,5,3,2"
			 * @return false if initialisation failed
			 */
			bool init(const Tick::Duration duration, size_t frameCount, uint8_t* frames);
			
			/**
			 * Initialisation used by the factory method, using all frames
			 * @param duration in second
			 * @return false if initialisation failed
			 */
			bool init(const Tick::Duration duration);
			
			/**
			 * Start the rotation on the specified receiver
			 * @param receiver the Sprite which receive the action
			 * @todo test the case when sprite is NULL
			 */
			virtual void start(Action_Receiver *receiver);
			
			/**
			 * called once per frame. time a value between 0 and 1
			 * For example:
			 * - 0 means that the action just started
			 * - 0.5 means that the action is in the middle
			 * - 1 means that the action is over
			 */
			virtual void update(const Percentage percentage);
			
			/**
			 * Called when the game is paused
			 * @todo implement it
			 */
			virtual void pause() {};
			
			/**
			 * Destructor
			 * @todo stop the action properly
			 */
			virtual ~SpriteActionAnimation();
			
		protected:
			/**
			 * Default Constructor
			 */
			SpriteActionAnimation();
			
			/** ID of the frames to diplay, ordered */
			// @todo maybe we don't need it to be a pointer ?
			std::vector<uint8_t>* _frameIDs;
			
			/** Current index in _frameIDs, ie frame displayed is _frameIDs[_frameIDIndexCurrent] */
			std::vector<uint8_t>::size_type _frameIDIndexCurrent;
			
			/** Index to show regarding the percentage of the action */
			std::vector<uint8_t>::size_type _frameIDIndexToShow;
			
			/** Option to use all frame in natural order, when true _frameIDs[1] == 1, _frameIDs[n] == n */
			bool _useAllFrames;
			
		private:
			
			/** Concrete receiver */
			Sprite *_receiver;
			
			/** Disable copying */
			DISALLOW_COPY_AND_ASSIGN(SpriteActionAnimation);
		};
	}
}


#endif




