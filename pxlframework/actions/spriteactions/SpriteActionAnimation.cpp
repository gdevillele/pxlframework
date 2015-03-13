//
//  SpriteActionAnimation.cpp
//  pxlframework
//
//  Created by Adrien Duermaël on 5/28/14.
//
//


#include "SpriteActionAnimation.h"

// C++
#include <limits>
// pxlframework
#include "Sprite.h"


namespace px
{
	namespace engine
	{
		/*static*/ SpriteActionAnimation* SpriteActionAnimation::withDuration(const Tick::Duration duration)
		{
			SpriteActionAnimation* action = new SpriteActionAnimation();
			
			if( ! action->init(duration))
			{
				delete action;
				action = nullptr;
			}
			return action;
		}
		
		
		bool SpriteActionAnimation::init(const Tick::Duration duration, size_t frameCount, uint8_t* frames)
		{
			if((frameCount > 0) && Action::init(duration))
			{
				for(int i = 0; i < frameCount; ++i)
				{
					_frameIDs->push_back(frames[i]);
				}
				_frameIDIndexCurrent = -1; // So first update will update the display
				
				return true;
			}
			return false;
		}
		
		
		bool SpriteActionAnimation::init(const Tick::Duration duration) // Use all frames
		{
			if(Action::init(duration))
			{
				_frameIDIndexCurrent = -1; // So first update will update the display
				_useAllFrames = true;
				return true;
			}
			return false;
		}
		
		/*virtual*/ void SpriteActionAnimation::start(Action_Receiver *receiver)
		{
			Action::start(receiver);
			_receiver = static_cast<Sprite*>(receiver);
			
			if(_useAllFrames)
			{
				if(_receiver == nullptr)
				{
					_frameIDs->push_back(0); // In this state, the animation isn't valid
					return;
				}
				// Compute aviable frames
				uint8_t max = _receiver->getNbFrames();
				for(uint8_t i = 0; i < max; ++i)
				{
					_frameIDs->push_back(i);
				}
			}
		}
		
		
		/*virtual*/ void SpriteActionAnimation::update(const Percentage percentage)
		{
			if(!_receiver)
			{
				return;
			}
			
			// Compute frame to set
			static float one = 1.0f - std::numeric_limits<float>::epsilon();
			_frameIDIndexToShow = (_frameIDs->size() * std::min(percentage, one));
			if(_frameIDIndexCurrent != _frameIDIndexToShow)
			{
				_frameIDIndexCurrent = _frameIDIndexToShow;
				_receiver->setCurrentFrame(_frameIDs->at(_frameIDIndexCurrent));
			}
			
		}
		
        
		SpriteActionAnimation::SpriteActionAnimation() : Action(),
		_frameIDs(new std::vector<uint8_t>()),
		_frameIDIndexCurrent(0),
		_frameIDIndexToShow(0),
		_useAllFrames(false),
		_receiver(nullptr)
		{
			
		}
		
		/*virtual*/ SpriteActionAnimation::~SpriteActionAnimation()
		{
			delete _frameIDs;
			_frameIDs = nullptr;
		}
	}
}




