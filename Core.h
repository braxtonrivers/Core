#pragma once

#ifdef _WIN32
	#define WIN32_LEAN_AND_MEAN
	#include <windows.h>
	#include <stdlib.h>
	#include <Shellapi.h>

	#include "Win32\CoreObject.h"
	#include "Win32\CoreImage.h"
	#include "Win32\CoreWindow.h"
	//#include "CoreSubWindow.h"
	#include "Win32\CoreFont.h"
#endif