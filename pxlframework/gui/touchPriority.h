//
//  touchPriority.h
//  pxlframework
//
//  Created by Gaëtan de Villèle on 2/5/14.
//
//


#ifndef __pxlframework__touchPriority__
#define __pxlframework__touchPriority__


// TODO: remove that file from the framework... it's game-specific stuff...
namespace touchPriority
{
	const uint8_t default_menu = 5;
	
	const uint8_t alert_popup = 3; // HIGH
	const uint8_t menu_popup  = 4;
	const uint8_t menu        = 5;
	const uint8_t game        = 6; // LOW
}


#endif




