
#include <stdlib.h>
#include <X11/X.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <stdio.h>
#include <string.h>

/*
#include <limits.h>
#include <X11/keysym.h>
#include <X11/Xatom.h>
#include <X11/extensions/xf86vmode.h>
*/

extern "C"
{
	int MyFunc();
}

int MyFunc()
{
	int x=100;
	int y=100;
	
	XSetWindowAttributes swa;
	Display* display = XOpenDisplay(NULL);
	
    int screen = DefaultScreen(display);
    Visual* visual = DefaultVisual(display,screen);
    int depth  = DefaultDepth(display,screen);
	
    swa.background_pixel = XWhitePixel(display,screen);
	
    Window win1 = XCreateWindow( display, XRootWindow(display,screen), x, y, 1024, 768, 5, depth, InputOutput, visual, CWBackPixel, &swa);
	XSetStandardProperties(display, win1, "Core Window Test", "Core Window Test", 0L, NULL, 0, NULL);
	
	Atom wmDeleteMessage = XInternAtom(display, "WM_DELETE_WINDOW", False);
	XSetWMProtocols(display, win1, &wmDeleteMessage, 1);
	
    XSelectInput(display,win1,ExposureMask|KeyPressMask);
	
	XMapWindow(display,win1);
	XMoveWindow(display,win1,x,y);
	
	XGCValues gr_values;
	GC gr_context1;
	
	gr_values.function =   GXcopy; 
	gr_values.plane_mask = AllPlanes; 
	gr_values.foreground = BlackPixel(display,screen); 
	gr_values.background = WhitePixel(display,screen); 
	gr_context1=XCreateGC(display,win1, GCFunction | GCPlaneMask | GCForeground | GCBackground, &gr_values); 
	
	Colormap cmap = DefaultColormap(display,screen);
	XColor xcolour;
	
	//Set background color
	xcolour.red = 62*64000/256; xcolour.green = 62*64000/256; xcolour.blue = 62*64000/256;
	xcolour.flags = DoRed | DoGreen | DoBlue;
	XAllocColor(display, cmap, &xcolour);	
	XSetWindowBackground(display,win1,xcolour.pixel);
	
	XEvent event;
	while (true)
	{
		XNextEvent(display,&event);
		switch(event.type)
		{
		case Expose:
			xcolour.red = 255*64000/256; xcolour.green = 255*64000/256; xcolour.blue = 255*64000/256;
			xcolour.flags = DoRed | DoGreen | DoBlue;
			XAllocColor(display, cmap, &xcolour);
			XSetForeground(display, gr_context1, xcolour.pixel);			
			XClearWindow(display,win1);
			
			//XSetClipRectangles();// clipping region
			
			XDrawString(display, win1, gr_context1, 50, 50, "Hello Linux World", strlen("Hello Linux World"));
			
			//XFillRectangle(display,win1,gr_context1,50,50,300,300);
			break;
			
		case ClientMessage:
			if (event.xclient.data.l[0] == wmDeleteMessage) return 2;
			break;
			
		case KeyPress:
			break;
		}
	}
}