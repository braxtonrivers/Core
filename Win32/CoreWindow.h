#pragma once

#include "Core.h"

class CoreWindow : public CoreObject
{
public:
	char* text;
	HWND hwnd;
	HDC hdc;
	RECT rect;
	RECT clientrect;
	HRGN hrgn;
	char background[4];
	char color[4];
	HBRUSH bgbrush;
	HBRUSH fgbrush;
	CoreWindow* parent;
	CoreWindow* child;
	CoreWindow* sibling;
	void (*Callback)(CoreWindow*,int,int,int);
	bool issubwindow;
	bool clipmode;
	int clipregion[4];
	
	CoreWindow();
	virtual ~CoreWindow();
	
	void SetShape(int x, int y, int width, int height);
	void SetClipRegion(int x, int y, int width, int height, bool clip);
	HWND GetHandle();
	int GetX();
	int GetY();
	int GetWidth();
	int GetHeight();
	int ClientWidth();
	int ClientHeight();
	virtual bool Initialize(char* title, int x, int y, int width, int height, CoreWindow* parent, int style);
	virtual void Draw();
	void Clear();
	virtual void UpdateCoords();
	void SetColor(int r, int g, int b, int bg);
	void DrawRect(int x, int y, int width, int height);
	void DrawText(char* text, int x, int y, int width, int height, int style);
	void SetText(char* text);
	void DrawImage(CoreImage* img, int x, int y, int width, int height);

	static bool WindowClassInitialized;
	static bool InitializeWindowClass();
};

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);