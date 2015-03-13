/**
 * Includes every file related to the actions
 *
 * @author Axel Guilmin
 * @date 10/14/13
 */


// Main
#include "Action.h"
#include "Action_Receiver.h"

// Modifiers
#include "ActionSequence.h"
#include "ActionEaseInOut.h"
#include "ActionEaseIn.h"
#include "ActionRepeatForever.h"

// Callbacks
#include "ActionCallback.h"

// Wait
#include "ActionWait.h"

// SpriteActions
#include "SpriteActionScaleTo.h"
#include "SpriteActionRotateBy.h"
#include "SpriteActionMoveBy.h"
#include "SpriteActionMoveTo.h"
#include "SpriteActionFadeTo.h"
#include "SpriteActionTintTo.h"
#include "SpriteActionCropTo.h"
#include "SpriteActionAnimation.h"

// ScrollViewActions
#include "ScrollViewActionScrollTo.h"
#include "ScrollViewActionLock.h"
#include "ScrollViewActionUnlock.h"


// Action examples

//// 1 - Move to the top right of the screen
//grubHead->runAction(WorldElementActionMoveTo::withDuration(1.0f, Point::createWith3DCoords(2048, 1536)));
//
//// 2 - Move by 200,200 in the 2D landmark with easing
//grubHead->runAction(ActionEaseInOut::withRatio(2.0f, WorldElementActionMoveBy::withDuration(1.0f, Point::createWith2DCoords(200, 200))));
//
//// 3 - Infinite rotation
//Action::ActionUID uid = grubHead->runAction(ActionRepeatForever::withAction(
//                                                  WorldElementActionRotateBy::withDuration(1.0f, 360.0f)));
//
//// 3 - Stop the infinite rotation
//grubHead->stopAction(uid);
//
//// 4 - Other ways to stop the actions
//grubHead->stopActions<ActionRepeatForever>();
//grubHead->stopAllActions();
//
//// 5 - Create a keyframe animation with selected frames
//grubHead->runAction(WorldElementActionAnimation::withDurationAndFrames(0.8f, 0,1,2,3,4,5,6,7,8,9,8,7,6,5,4,3,2,1))));
//
//// 6 - Repeating animation, using all frame availables
//grubHead->runAction(ActionRepeatForever::withAction(
//                          WorldElementActionAnimation::withDuration(2.0f)));
//
//// 7 - Do a losange shape moving with funny spining in the middle
//grubHead->runAction(ActionSequence::withActions(
//                                                      ActionEaseInOut::withRatio(2.0f, WorldElementActionMoveBy::withDuration(1.0f, Point::createWith3DCoords(200, 200))),
//                                                      ActionEaseInOut::withRatio(2.0f, WorldElementActionMoveBy::withDuration(1.0f, Point::createWith3DCoords(-200, 200))),
//                                                      ActionEaseInOut::withRatio(2.0f, WorldElementActionRotateBy::withDuration(2.0f, 1080.0f)),
//                                                      ActionEaseInOut::withRatio(2.0f, WorldElementActionRotateBy::withDuration(2.0f, -2160.0f)),
//                                                      ActionEaseInOut::withRatio(2.0f, WorldElementActionMoveBy::withDuration(1.0f, Point::createWith3DCoords(-200, -200))),
//                                                      ActionEaseInOut::withRatio(2.0f, WorldElementActionMoveBy::withDuration(1.0f, Point::createWith3DCoords(200, -200)))
//                                                      ));




