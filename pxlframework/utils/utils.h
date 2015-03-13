//
//  utils.h
//  pxlframework
//
//  Created by Adrien Duermaël on 4/21/14.
//
//


#ifndef __pxlframework__utils__
#define __pxlframework__utils__


// C++
#include <cassert>
#include <sstream>
//
//#include <CrashlyticsInterface.h>


// convert things to string
template <typename T> std::string tostr(const T& t)
{
	std::ostringstream os; os<<t; return os.str();
}


//#define PXL_ASSERT_DETAILED(_CONDITION, _DETAILS) \
//{ \
//if(!(_CONDITION)) \
//{ \
//std::string details = std::string(__FILE__) + ":" + tostr(__func__) + ":" + tostr(__LINE__) + " - " + tostr(_DETAILS); \
//px::sdk::CrashlyticsInterface::logHandledException("assertion failed", details); \
//assert(_CONDITION); \
//} \
//}

#define PXL_ASSERT_DETAILED(_CONDITION, _DETAILS) \
{ \
if(!(_CONDITION)) \
{ \
assert(_CONDITION); \
} \
}

//#define PXL_ASSERT(_CONDITION) \
//{\
//if(!(_CONDITION)) \
//{ \
//std::string details = std::string(__FILE__) + ":" + std::string(__func__) + ":" + tostr(__LINE__); \
//px::sdk::CrashlyticsInterface::logHandledException("assertion failed", details); \
//assert(_CONDITION); \
//} \
//}

#define PXL_ASSERT(_CONDITION) \
{\
if(!(_CONDITION)) \
{ \
assert(_CONDITION); \
} \
}





#ifndef PXL_TARGET_PLATFORM
// Determining the target platform
//////////////////////////////////////////////////////////////////////
// pre configure
//////////////////////////////////////////////////////////////////////

// define supported target platform macro which CC uses.
#define PXL_PLATFORM_UNKNOWN            0
#define PXL_PLATFORM_IOS                1
#define PXL_PLATFORM_ANDROID            2
//#define PXL_PLATFORM_WIN32              3
//#define PXL_PLATFORM_MARMALADE          4
//#define PXL_PLATFORM_LINUX              5
//#define PXL_PLATFORM_BADA               6
//#define PXL_PLATFORM_BLACKBERRY         7
//#define PXL_PLATFORM_MAC                8

// Determine target platform by compile environment macro.
#define PXL_TARGET_PLATFORM             PXL_PLATFORM_UNKNOWN

// android
#if ! PXL_TARGET_PLATFORM && defined(ANDROID)
#undef  PXL_TARGET_PLATFORM
#define PXL_TARGET_PLATFORM         PXL_PLATFORM_ANDROID
#endif

// iphone
#if ! PXL_TARGET_PLATFORM
#include "TargetConditionals.h"
#if defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR)
#undef  PXL_TARGET_PLATFORM
#define PXL_TARGET_PLATFORM         PXL_PLATFORM_IOS
#endif
#endif

//////////////////////////////////////////////////////////////////////////
// post configure
//////////////////////////////////////////////////////////////////////////

// check user set platform
#if ! PXL_TARGET_PLATFORM
#error  "[PXLTOOLS] Cannot recognize the target platform; are you targeting an unsupported platform?"
#endif

#endif


//////////////////////////////////////////////////////////////////////
///
/// iOS
///
//////////////////////////////////////////////////////////////////////
// define the LOG macro for iOS
#if (PXL_TARGET_PLATFORM == PXL_PLATFORM_IOS)
#ifdef NDEBUG
//#define PXLLOG( format, ... )   { px::sdk::CrashlyticsInterface::log(format, ##__VA_ARGS__ ); }
#define PXLLOG( format, ... )
#else
//#define PXLLOG( format, ... )   { printf("[grub] ");px::sdk::CrashlyticsInterface::log(format, ##__VA_ARGS__ ); printf(format, ##__VA_ARGS__ ); printf("\n"); }
#define PXLLOG( format, ... )   { printf("[grub] "); printf(format, ##__VA_ARGS__ ); printf("\n"); }
#endif
#endif

//////////////////////////////////////////////////////////////////////
///
/// Android
///
//////////////////////////////////////////////////////////////////////
// define the LOG macro for Android
#if (PXL_TARGET_PLATFORM == PXL_PLATFORM_ANDROID)
#if NDEBUG
#include <android/log.h>
#define PXLLOG( format, ... )   { __android_log_print(ANDROID_LOG_ERROR, "[pxltools]", format, ##__VA_ARGS__ ); }
#else
#include <android/log.h>
#define PXLLOG( format, ... )   { __android_log_print(ANDROID_LOG_ERROR, "[pxltools]", format, ##__VA_ARGS__ ); }
//#define TOOLS_LOG( format, ... )   __android_log_print( ANDROID_LOG_VERBOSE, "Pixowl LOG", format, ##__VA_ARGS__ )
//#define TOOLS_LOG_D( format, ... ) __android_log_print( ANDROID_LOG_DEBUG,   "Pixowl LOG", format, ##__VA_ARGS__ )
//#define TOOLS_LOG_W( format, ... ) __android_log_print( ANDROID_LOG_WARN,    "Pixowl LOG", format, ##__VA_ARGS__ )
//#define TOOLS_LOG_E( format, ... ) __android_log_print( ANDROID_LOG_ERROR,   "Pixowl LOG", format, ##__VA_ARGS__ )
#endif
#endif
#endif



