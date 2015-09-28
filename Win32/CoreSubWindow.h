#pragma once

#include "Core.h"

class CoreSubWindow : public CoreWindow
{
public:
	virtual bool Initialize(char* title, const int x, const int y, const int width, const int height, CoreWindow* parent, int style);
	virtual void UpdateCoords();
};