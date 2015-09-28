#pragma once

#include "Core.h"

class CoreFont : public CoreObject
{
public:
	HFONT handle;
	
	CoreFont();
	~CoreFont();

	static CoreFont* Default;
	static CoreFont* Status;
	static CoreFont* Message;
	static CoreFont* Menu;
};
