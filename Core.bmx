SuperStrict

Import brl.pixmap

?win32
Import "Win32\Core.cpp"
Import "Win32\CoreWindow.cpp"
Import "Win32\CoreFont.cpp"
Import "Win32\CoreSubWindow.cpp"
Import "Win32\CoreImage.cpp"
?

?macos
Import "MacOS\Core.cpp"
Import "MacOS\CoreWindow.cpp"
Import "MacOS\CoreFont.cpp"
Import "MacOS\CoreSubWindow.cpp"
Import "MacOS\CoreImage.cpp"
?

?linux
Import "Linux\Core.cpp"
Import "Linux\CoreWindow.cpp"
Import "Linux\CoreFont.cpp"
Import "Linux\CoreSubWindow.cpp"
Import "Linux\CoreImage.cpp"
?

Const CORE_TEXT_WRAP:Int=1
Const CORE_TEXT_CENTER:Int=2
Const CORE_TEXT_VCENTER:Int=4

Const CORE_WINDOW_TITLEBAR:Int=1
Const CORE_WINDOW_RESIZABLE:Int=2
Const CORE_WINDOW_TOOL:Int=4
Const CORE_WINDOW_HIDDEN:Int=8
Const CORE_WINDOW_ACCEPTFILES:Int=16

Const CORE_EVENT_WINDOW_PAINT:Int=1
Const CORE_EVENT_WINDOW_CLOSE:Int=2
Const CORE_EVENT_WINDOW_SIZE:Int=4

Const CORE_WINDOW_DEFAULT:Int=CORE_WINDOW_TITLEBAR|CORE_WINDOW_RESIZABLE

Extern "C"
	
	Type TCoreObject
	EndType
	
	Type TCoreWindow Extends TCoreObject
	EndType
	
	Type TCoreSubWindow Extends TCoreWindow
	EndType
	
	Type TCoreFont Extends TCoreObject
	EndType
	
	Type TCoreImage Extends TCoreObject
	EndType
	
	Function CoreWindowSetShape(win:TCoreWindow,x:Int,y:Int,width:Int,height:Int)
	Function CoreWindowSetClipRegion(win:TCoreWindow,x:Int,y:Int,width:Int,height:Int,clip:Int)
	Function CoreImageGetWidth:Int(img:TCoreImage)
	Function CoreImageGetHeight:Int(img:TCoreImage)
	Function CoreDeleteObject(o:Byte Ptr)
	Function CoreImageCreate:TCoreImage(width:Int,height:Int,format:Int,pixels:Byte Ptr)
	Function CoreWindowDrawImage(img:TCoreImage,x:Int,y:Int,width:Int,height:Int)
	Function CoreWindowDrawRect(win:TCoreWindow,x:Int,y:Int,width:Int,height:Int)	
	Function CoreWindowDrawText(win:TCoreWindow,text$z,x:Int,y:Int,width:Int,height:Int,style:Int)
	Function CoreWindowClear(win:TCoreWindow)
	Function CoreWindowSetText(win:TCoreWindow,text$z)
	Function CoreWindowSetCallback(win:TCoreWindow,Callback(win:TCoreWindow, event_id:Int, x:Int, y:Int ))
	Function CoreWindowGetHandle:Byte Ptr(win:TCoreWindow)
	Function CoreWindowSetColor(win:TCoreWindow,r%,g%,b%,bg%)
	Function CoreCreateWindow:TCoreWindow(title$z,x:Int,y:Int,width:Int,height:Int,parent:TCoreWindow,style:Int)
	Function CoreCreateSubWindow:TCoreWindow(title$z,x:Int,y:Int,width:Int,height:Int,parent:TCoreWindow,style:Int)
	Function CoreWindowClientWidth:Int(win:TCoreWindow)
	Function CoreWindowClientHeight:Int(win:TCoreWindow)
	Function CoreWindowGetX:Int(win:TCoreWindow)
	Function CoreWindowGetY:Int(win:TCoreWindow)
	Function CoreWindowGetWidth:Int(win:TCoreWindow)
	Function CoreWindowGetHeight:Int(win:TCoreWindow)
	
EndExtern

Function CoreLoadImage:TCoreImage(file:String)
	Local pixmap:TPixmap=LoadPixmap(file)
	If Not pixmap Return Null
	Local bpp:Int=4
	Select pixmap.format
	Case PF_RGB888
		bpp=3
	Case PF_RGBA8888
	Case PF_BGR888
		pixmap=ConvertPixmap(pixmap,PF_RGB888)
		bpp=3
	Case PF_BGRA8888 pixmap=ConvertPixmap(pixmap,PF_RGBA8888)
	Default pixmap=ConvertPixmap(pixmap,PF_RGBA8888)
	EndSelect
	Return CoreImageCreate(pixmap.width,pixmap.height,bpp,pixmap.pixels)
EndFunction
