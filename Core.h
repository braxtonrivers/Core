#pragma once

#ifdef _WIN32
	#define WIN32_LEAN_AND_MEAN
	#include <windows.h>
	#include <stdlib.h>
	#include <Shellapi.h>
	
	#include "Win32\CoreObject.h"
	#include "Win32\CoreImage.h"
	#include "Win32\CoreWindow.h"
	#include "Win32\CoreFont.h"
#endif

#ifdef __linux__
	#include <stdlib.h>
	#include <X11/X.h>
	#include <GL/gl.h>
	#include <GL/glx.h>
	#include <stdio.h>
	#include <string.h>	

	#include "Linux/CoreObject.h"
	#include "Linux/CoreImage.h"
	#include "Linux/CoreWindow.h"
	#include "Linux/CoreFont.h"
#endif

extern "C"
{
	void CoreWindowSetShape(CoreWindow* window, int x, int y, int width, int height);
	void CoreWindowSetClipRegion(CoreWindow* window, int x, int y, int width, int height, int clip);
	int CoreImageGetWidth(CoreImage* img);
	int CoreImageGetHeight(CoreImage* img);
	void CoreDeleteObject(CoreObject* o);
	CoreImage* CoreImageCreate(int width, int height, int format, void* pixels);
	void CoreWindowDrawImage(CoreImage* img, int x, int y, int width, int height);
	void CoreWindowDrawRect(CoreWindow* win, int x, int y, int width, int height);
	void CoreWindowDrawText(CoreWindow* win, char* text, int x, int y, int width, int height, int style);
	CoreWindow* CoreCreateWindow(char* title, int x, int y, int width, int height, CoreWindow* parent, int style);
	//CoreSubWindow* CoreCreateSubWindow(char* title, int x, int y, int width, int height, CoreWindow* parent, int style);
	void CoreWindowClear(CoreWindow* win);
	void CoreWindowSetText(CoreWindow* win, char* text);
	void CoreWindowSetCallback(CoreWindow* win, void (*Callback)(CoreWindow*,int,int,int,int,int) );
	void* CoreWindowGetHandle(CoreWindow* win);
	void CoreWindowSetColor(CoreWindow* win, int r, int g, int b, int bg);
	int CoreWindowGetX(CoreWindow* win);
	int CoreWindowGetY(CoreWindow* win);
	int CoreWindowGetWidth(CoreWindow* win);
	int CoreWindowGetHeight(CoreWindow* win);
	int CoreWindowClientWidth(CoreWindow* win);
	int CoreWindowClientHeight(CoreWindow* win);
}

