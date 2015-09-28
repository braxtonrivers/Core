#include "Core.h"

bool CoreSubWindow::Initialize(char* title, int x, int y, int width, int height, CoreWindow* parent, int style)
{
	if (hwnd) return false;
	if (parent==NULL) return false;
	
	issubwindow = true;
	
	SetText(title);
	
	//Create window
	hwnd = CreateWindowExA(0,"CORE_WINDOW_CLASS",NULL,WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN|WS_CLIPSIBLINGS,x,y,width,height,parent->hwnd,NULL,NULL,NULL);
	
	if (hwnd==NULL) return false;
	SetWindowLongA(hwnd,-10,NULL);
		
	GetWindowRect(hwnd,&rect);
    MapWindowPoints(HWND_DESKTOP, GetParent(hwnd), (LPPOINT) &rect, 2);	
	GetClientRect(hwnd,&clientrect);
	
	SetWindowLongPtrA(hwnd,GWLP_USERDATA,(LONG_PTR)this);
	
	this->parent = parent;
	parent->child = this;
	
	hdc = GetDC(hwnd);
	return true;
}

void CoreSubWindow::UpdateCoords()
{
	GetWindowRect(hwnd,&rect);
	MapWindowPoints(HWND_DESKTOP, parent->hwnd, (LPPOINT) &rect, 2);	
	GetClientRect(hwnd,&clientrect);
}
