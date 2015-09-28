#include "Core.h"

bool CoreWindow::WindowClassInitialized=false;

const int CORE_TEXT_WRAP = 1;
const int CORE_TEXT_CENTER = 2;
const int CORE_TEXT_VCENTER = 4;

const int CORE_WINDOW_TITLEBAR=1;
const int CORE_WINDOW_RESIZABLE=2;
const int CORE_WINDOW_TOOL=4;
const int CORE_WINDOW_HIDDEN=8;
const int CORE_WINDOW_ACCEPTFILES=16;

const int CORE_EVENT_WINDOW_PAINT=1;
const int CORE_EVENT_WINDOW_CLOSE=2;
const int CORE_EVENT_WINDOW_SIZE=4;

CoreWindow::CoreWindow()
{
	clipmode=false;

	issubwindow = false;
	Callback = NULL;

	hrgn = NULL;
	hwnd = NULL;
	hdc = NULL;
	
	child = NULL;
	sibling = NULL;
	parent = NULL;
	hwnd = NULL;
	
	text = NULL;
	
	background[0]=64;
	background[1]=64;
	background[2]=64;
	background[3]=255;
	
	color[0]=255;
	color[1]=255;
	color[2]=255;
	color[3]=255;
	
	bgbrush = CreateSolidBrush(RGB(background[0],background[1],background[2]));
	fgbrush = CreateSolidBrush(RGB(color[0],color[1],color[2]));
}

CoreWindow::~CoreWindow()
{
	if (text!=NULL)
	{
		free(text);
		text = NULL;
	}
	CoreWindow* firstchild = child;
	while (firstchild)
	{
		child = firstchild;
		firstchild = child->sibling;
		delete child;
	}
	if (hrgn)
	{
		DeleteObject(hrgn);
		hrgn = NULL;
	}
}

HWND CoreWindow::GetHandle()
{
	return hwnd;
}

int CoreWindow::GetX()
{
	return rect.left;
}

int CoreWindow::GetY()
{
	return rect.top;
}

int CoreWindow::GetWidth()
{
	return rect.right-rect.left;
}

int CoreWindow::GetHeight()
{
	return rect.bottom-rect.top;
}

int CoreWindow::ClientWidth()
{
	return clientrect.right-clientrect.left;
}

int CoreWindow::ClientHeight()
{
	return clientrect.bottom-clientrect.top;
}

bool CoreWindow::Initialize(char* title, int x, int y, int width, int height, CoreWindow* parent, int style)
{
	if (hwnd) return false;

	InitializeWindowClass();
	
	//style = 2;//+2;//+8+16;
	
	int wstyle = WS_POPUP | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
	int xstyle = 0;//CS_HREDRAW | CS_VREDRAW;// | WS_EX_DLGMODALFRAME;
	
	if (style & CORE_WINDOW_TITLEBAR)
	{
		wstyle |= WS_CAPTION | WS_SYSMENU;
	}
	else
	{
		wstyle |= WS_POPUPWINDOW;
	}
	if (style & CORE_WINDOW_RESIZABLE) wstyle |= WS_MAXIMIZEBOX | WS_MINIMIZEBOX |  WS_THICKFRAME;
	if (style & CORE_WINDOW_TOOL) xstyle |= WS_EX_TOOLWINDOW;// | WS_POPUPWINDOW | ~WS_THICKFRAME;
	
	SetText(title);
	
	//Create window
	HWND parenthwnd = NULL;
	if (parent!=NULL) parenthwnd = parent->hwnd;
	hwnd=CreateWindowExA(xstyle,"CORE_WINDOW_CLASS",title,wstyle,x,y,width,height,parenthwnd,NULL,NULL,NULL);
	if (hwnd==NULL) return false;
	SetWindowLongA(hwnd,-10,0);
	SetWindowLongPtrA(hwnd,GWLP_USERDATA,(LONG_PTR)this);
	
	//
	
	GetWindowRect(hwnd,&rect);
	GetClientRect(hwnd,&clientrect);

	hdc = GetDC(hwnd);
	
	if (!(style & CORE_WINDOW_HIDDEN)) ShowWindow(hwnd,1);
	//if (style & CORE_WINDOW_ACCEPTFILES) DragAcceptFiles(hwnd,true);
	
	return true;
}

void CoreWindow::Draw()
{
	if (Callback!=NULL)
	{
		Callback(this,CORE_EVENT_WINDOW_PAINT,0,0);
	}
	else
	{
		Clear();
		if (text!="") this->DrawText(text,2,2,0,0,0);
	}
}

void CoreWindow::Clear()
{
	FillRect(hdc,&clientrect,bgbrush);
}

void CoreWindow::DrawRect(int x, int y, int width, int height)
{
	RECT rect;
	rect.left=x;
	rect.top=y;
	rect.right=x+width;
	rect.bottom=y+height;
	FillRect(hdc,&rect,fgbrush);
}

void CoreWindow::SetClipRegion(int x, int y, int width, int height, bool clip)
{
	if (clip!=clipmode || x!=clipregion[0] || y!=clipregion[1] || width != clipregion[2] || height != clipregion[3])
	{
		clipregion[0]=x;
		clipregion[1]=y;
		clipregion[2]=width;
		clipregion[3]=height;
		clipmode=clip;
		if (hrgn)
		{
			DeleteObject(hrgn);
			hrgn = NULL;
		}
		if (clip) hrgn = CreateRectRgn(x,y,x+width,y+height);
	    SelectClipRgn(hdc, hrgn);
	}
}

void CoreWindow::DrawText(char* text, int x, int y, int width, int height, int style)
{
	RECT rect;
	rect.left=x;
	rect.top=y;
	rect.right=x+width;
	rect.bottom=y+height;
	
	SetBkMode(hdc,TRANSPARENT);
	SetTextColor(hdc,RGB(color[0],color[1],color[2]));
	
	SelectObject(hdc,CoreFont::Menu->handle);
	
	int flags = 0;
	//DT_CENTER|DT_VCENTER|DT_SINGLELINE
	
	if (style & CORE_TEXT_CENTER) flags |= DT_CENTER;	
	if (!(style & CORE_TEXT_WRAP))
	{
		flags |= DT_SINGLELINE;
		if (style & CORE_TEXT_VCENTER) flags |= DT_VCENTER;
		//::DrawText(hdc,text,-1,&rect,DT_CALCRECT);
	}
	
	flags|=DT_WORDBREAK;
	
	//flags=DT_WORD_ELLIPSIS;//truncates text
	
	//Draw
	::DrawText(hdc,text,-1,&rect,flags);
	
	SetBkMode(hdc,OPAQUE);	
}

bool CoreWindow::InitializeWindowClass()
{
	if (!WindowClassInitialized)
	{
		WindowClassInitialized = true;
		WNDCLASS wndclass;
		wndclass.cbClsExtra = 0;
		wndclass.cbWndExtra = 0;
		wndclass.hbrBackground = NULL;//(HBRUSH)GetStockObject(NULL_BRUSH);
		wndclass.hCursor = LoadCursor( NULL, IDC_ARROW );
		wndclass.hIcon = LoadIcon( NULL, IDI_APPLICATION );
		wndclass.lpfnWndProc = WndProc;
		wndclass.lpszClassName = TEXT("CORE_WINDOW_CLASS");
		wndclass.lpszMenuName = 0;
		wndclass.style = CS_HREDRAW|CS_VREDRAW|CS_OWNDC;
		RegisterClass( &wndclass );
		
		NONCLIENTMETRICS ncm;
		
		CoreFont::Menu = new CoreFont;		
		ncm.cbSize = sizeof(NONCLIENTMETRICS);
		SystemParametersInfo(SPI_GETNONCLIENTMETRICS,sizeof(NONCLIENTMETRICS),&ncm,0);
		CoreFont::Menu->handle = CreateFontIndirect(&ncm.lfMenuFont);
		
		CoreFont::Status = new CoreFont;
		ncm.cbSize = sizeof(NONCLIENTMETRICS);
		SystemParametersInfo(SPI_GETNONCLIENTMETRICS,sizeof(NONCLIENTMETRICS),&ncm,0);
		CoreFont::Status->handle = CreateFontIndirect(&ncm.lfStatusFont);
		
		CoreFont::Message = new CoreFont;
		ncm.cbSize = sizeof(NONCLIENTMETRICS);
		SystemParametersInfo(SPI_GETNONCLIENTMETRICS,sizeof(NONCLIENTMETRICS),&ncm,0);
		CoreFont::Message->handle = CreateFontIndirect(&ncm.lfMessageFont);
		
		CoreFont::Default = new CoreFont;
		CoreFont::Default->handle = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
	}
}

void CoreWindow::SetText(char* text)
{
	if (this->text!=NULL) free(this->text);
	this->text = (char*)malloc(strlen(text) + 1); 
	strcpy(this->text,text);
}

void CoreWindow::SetColor(int r, int g, int b, int bg)
{
	if (bg==0)
	{
		if (r!=color[0] || g!=color[1] || b!=color[2])
		{
			color[0]=r; color[1]=g; color[2]=b;
			if (fgbrush) DeleteObject(fgbrush);
			fgbrush = CreateSolidBrush(RGB(color[0],color[1],color[2]));
		}
	}
	else
	{
		if (r!=background[0] || g!=background[1] || b!=background[2])
		{
			background[0]=r; background[1]=g; background[2]=b;
			if (bgbrush) DeleteObject(fgbrush);
			bgbrush = CreateSolidBrush(RGB(background[0],background[1],background[2]));
		}
	}
}

void CoreWindow::UpdateCoords()
{
	GetWindowRect(hwnd,&rect);
	GetClientRect(hwnd,&clientrect);
}

void CoreWindow::SetShape(int x, int y, int width, int height)
{
	rect.left=x;
	rect.right=x+width;
	rect.top=y;
	rect.bottom=y+height;
	MoveWindow(hwnd,x,y,width,height,true);
	UpdateCoords();
}

void CoreWindow::DrawImage(CoreImage* img, int x, int y, int width, int height)
{
/*
	'create a dc with this bitmap in
	Local hdcBitmap:Int = CreateCompatibleDC(deviceContext)
	Local oldBitmap:Int = SelectObject(hdcBitmap,img->bitmap)
	
	'paint it
	//If bitmap.hasAlpha
	//	AlphaBlend_(deviceContext,x,y,Width,Height,hdcBitmap,sourceX,sourceY,sourceWidth,sourceHeight,$01ff0000)
	//Else
	//	If sourceX = 0 And sourceY = 0 And sourceWidth = Width And sourceHeight = Height
	//		'no stretch
			BitBlt(deviceContext,x,y,bitmap.Width,bitmap.Height,hdcBitmap,0,0,ROP_SRCCOPY)
	//	Else
	//		'stretch
	//		StretchBlt(deviceContext,x,y,Width,Height,hdcBitmap,sourceX,sourceY,sourceWidth,sourceHeight,ROP_SRCCOPY)
	//	EndIf
	//EndIf
	
	//free it
	SelectObject(hdcBitmap,oldBitmap)
	DeleteDC(hdcBitmap)*/
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	if (GetWindowLongA(hwnd,GWLP_USERDATA)!=0)
	{
		CoreWindow* window = (CoreWindow*)GetWindowLongPtrA(hwnd,GWLP_USERDATA);
		switch (message)
		{
		case WM_CLOSE:
			if (window->Callback!=NULL) window->Callback(window,CORE_EVENT_WINDOW_CLOSE,0,0);
			return 0L;
			break;
		case WM_SIZE:
			if (LOWORD(lparam)!=window->rect.right - window->rect.left || HIWORD(lparam)!=window->rect.bottom - window->rect.top)
			{
				window->UpdateCoords();
				if (window->Callback!=NULL) window->Callback(window,CORE_EVENT_WINDOW_SIZE,LOWORD(lparam),HIWORD(lparam));
			}
			break;
		case WM_ERASEBKGND:
			break;
		case WM_PAINT:
			PAINTSTRUCT ps;
			BeginPaint(hwnd,&ps);
			window->Draw();
			EndPaint(hwnd,&ps);
			return 0L;
			break;
		}
	}
	return DefWindowProc(hwnd, message, wparam, lparam);
}
