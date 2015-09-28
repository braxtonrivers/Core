SuperStrict

'Framework brl.systemdefault BMXNG module
Import brl.eventqueue
Import "Core.bmx"

Global mainwin:TCoreWindow=CoreCreateWindow("Core Window Test",200,100,800,600,Null,CORE_WINDOW_DEFAULT)
CoreWindowSetColor mainwin,34,34,35,True
CoreWindowSetCallback(mainwin,MainWindowCallback)

Global subwin:TCoreWindow=CoreCreateWindow("Subwindow",40,40,CoreWindowClientWidth(mainwin)-200,CoreWindowClientHeight(mainwin)-60,mainwin,CORE_WINDOW_PANEL)
CoreWindowSetColor subwin,0,0,0,True

Global subwin2:TCoreWindow=CoreCreateWindow("Subwindow 2",50,50,CoreWindowClientWidth(subwin)-100,CoreWindowClientHeight(subwin)-100,subwin,CORE_WINDOW_PANEL)
CoreWindowSetColor subwin2,35,35,35,True
CoreWindowSetCallback(subwin2,SubWindowCallback)

'Global win2:TCoreWindow=CoreCreateWindow("Window 2",50,50,400,380,mainwin,CORE_WINDOW_DEFAULT)
'CoreWindowSetColor win2,35,35,35,True
'CoreWindowSetCallback(win2,MainWindowCallback)

Repeat
	WaitEvent()
Forever

End

Function MainWindowCallback(win:TCoreWindow, id:Int, x:Int, y:Int, width:Int, height:Int ) "C"
	Select id
	Case CORE_EVENT_WINDOW_CLOSE
		End
	Case CORE_EVENT_WINDOW_PAINT
		CoreWindowClear(win)
	Case CORE_EVENT_WINDOW_SIZE
		If win=mainwin
			CoreWindowSetShape subwin,40,40,CoreWindowClientWidth(win)-200,CoreWindowClientHeight(win)-60
			CoreWindowSetShape subwin2,50,50,CoreWindowClientWidth(subwin)-100,CoreWindowClientHeight(subwin)-100
		EndIf
	EndSelect
EndFunction

Function SubWindowCallback(win:TCoreWindow, id:Int, x:Int, y:Int, width:Int, height:Int ) "C"
	Select id
	Case CORE_EVENT_WINDOW_PAINT
		Local s:String="Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum."
		s=s+"~n~n"+s+"~n~n"+s
		CoreWindowSetClipRegion(win,50,50,200,200,False)
		CoreWindowSetColor(win,Rand(100),Rand(100),Rand(100),True)
		CoreWindowClear(win)
		CoreWindowSetClipRegion(win,x,y,width,height,True)
		CoreWindowSetColor(win,0,0,128,False)
		CoreWindowSetColor(win,Rand(100),Rand(100),Rand(100),0)
		CoreWindowDrawRect(win,0,0,CoreWindowClientWidth(win)/2,CoreWindowClientHeight(win))
		CoreWindowSetColor(win,255,255,255,False)
		CoreWindowDrawText(win,s,0,0,CoreWindowClientWidth(win),CoreWindowClientHeight(win),CORE_TEXT_CENTER|CORE_TEXT_wrap)
	EndSelect
EndFunction
