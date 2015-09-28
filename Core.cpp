#include "Core.h"

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

void CoreWindowSetShape(CoreWindow* window, int x, int y, int width, int height)
{
	window->SetShape(x,y,width,height);
}

void CoreWindowSetClipRegion(CoreWindow* window, int x, int y, int width, int height, int clip)
{
	window->SetClipRegion(x,y,width,height,clip);
}

int CoreImageGetWidth(CoreImage* img)
{
	return 0;
}

int CoreImageGetHeight(CoreImage* img)
{
	return 0;
}

void CoreDeleteObject(CoreObject* o)
{
	delete o;
}

CoreImage* CoreImageCreate(int width, int height, int format, void* pixels)
{
	return NULL;
}

void CoreWindowDrawImage(CoreImage* img, int x, int y, int width, int height)
{
	
}	

void CoreWindowDrawRect(CoreWindow* win, int x, int y, int width, int height)
{
	win->DrawRect(x,y,width,height);
}

void CoreWindowDrawText(CoreWindow* win, char* text, int x, int y, int width, int height, int style)
{
	win->DrawText(text,x,y,width,height,style);
}

void CoreWindowClear(CoreWindow* win)
{
	win->Clear();
}

void CoreWindowSetText(CoreWindow* win, char* text)
{
	win->SetText(text);
}

void CoreWindowSetCallback( CoreWindow* win, void (*Callback)(CoreWindow*,int,int,int,int,int) )
{
	win->Callback = Callback;
}

void* CoreWindowGetHandle(CoreWindow* win)
{
	return (void*)win->GetHandle();
}

void CoreWindowSetColor(CoreWindow* win, int r, int g, int b, int bg)
{
	win->SetColor(r,g,b,bg);
}

int CoreWindowGetX(CoreWindow* win)
{
	return win->GetX();
}

int CoreWindowGetY(CoreWindow* win)
{
	return win->GetY();
}

int CoreWindowGetWidth(CoreWindow* win)
{
	return win->GetWidth();
}

int CoreWindowGetHeight(CoreWindow* win)
{
	return win->GetHeight();
}

int CoreWindowClientWidth(CoreWindow* win)
{
	return win->ClientWidth();
}

int CoreWindowClientHeight(CoreWindow* win)
{
	return win->ClientHeight();
}

CoreWindow* CoreCreateWindow(char* title, int x, int y, int width, int height, CoreWindow* parent, int style)
{
	CoreWindow* win=new CoreWindow;
	if (win->Initialize(title,x,y,width,height,parent,style))
	{
		return win;
	}
	else
	{
		delete win;
		return NULL;
	}
}

/*
CoreSubWindow* CoreCreateSubWindow(char* title, int x, int y, int width, int height, CoreWindow* parent, int style)
{
	CoreSubWindow* win=new CoreSubWindow;
	if (win->Initialize(title,x,y,width,height,parent,style))
	{
		return win;
	}
	else
	{
		delete win;
		return NULL;
	}
}
*/