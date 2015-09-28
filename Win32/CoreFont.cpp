#include "Core.h"

CoreFont* CoreFont::Default = NULL;
CoreFont* CoreFont::Status = NULL;
CoreFont* CoreFont::Message = NULL;
CoreFont* CoreFont::Menu = NULL;

CoreFont::CoreFont() : handle(NULL) {}

CoreFont::~CoreFont()
{
	if (handle) DeleteObject(handle);
}