#pragma once

#include "..\Core.h"

class CoreImage : public CoreObject
{
	HBITMAP bitmap;
	
	int width;
	int height;
	int format;
	
	CoreImage();
	~CoreImage();
	
	bool Initialize(void* data);
};
