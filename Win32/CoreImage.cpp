#include "..\Core.h"

CoreImage::~CoreImage()
{
	if (bitmap)
	{
		//ReleaseObject(bitmap);
	}
}
	
bool CoreImage::Initialize(void* data)
{
		
		return true;
}