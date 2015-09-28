SuperStrict

'Framework brl.systemdefault BMXNG module
Import brl.eventqueue
Import "Core.bmx"

Global win:TCoreWindow=CoreCreateWindow("Core Window Test",200,100,800,600,Null,CORE_WINDOW_DEFAULT)
CoreWindowSetColor win,34,34,35,True
CoreWindowSetCallback(win,MainWindowCallback)

Global subwin:TCoreWindow=CoreCreateSubWindow("Subwindow",40,40,CoreWindowClientWidth(win)-200,CoreWindowClientHeight(win)-60,win,0)
CoreWindowSetColor subwin,0,0,0,True

Global subwin2:TCoreWindow=CoreCreateSubWindow("Subwindow 2",50,50,CoreWindowClientWidth(subwin)-100,CoreWindowClientHeight(subwin)-100,subwin,0)
CoreWindowSetColor subwin2,35,35,35,True
CoreWindowSetCallback(subwin2,SubWindowCallback)

Repeat
	WaitEvent()
Forever

End

Function MainWindowCallback(win:TCoreWindow, id:Int, x:Int, y:Int) "C"
	Select id
	Case CORE_EVENT_WINDOW_CLOSE
		End
	Case CORE_EVENT_WINDOW_PAINT
		CoreWindowClear(win)
	Case CORE_EVENT_WINDOW_SIZE
		CoreWindowSetShape subwin,40,40,CoreWindowClientWidth(win)-200,CoreWindowClientHeight(win)-60
		CoreWindowSetShape subwin2,50,50,CoreWindowClientWidth(subwin)-100,CoreWindowClientHeight(subwin)-100
	EndSelect
EndFunction
 
Function SubWindowCallback(win:TCoreWindow, id:Int, x:Int, y:Int) "C"
	Select id
	Case CORE_EVENT_WINDOW_PAINT
		Local s:String="Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum."
		s=s+"~n~n"+s+"~n~n"+s
		CoreWindowSetClipRegion(win,50,50,200,200,False)
		CoreWindowClear(win)
		CoreWindowSetClipRegion(win,50,50,200,200,True)
		CoreWindowSetColor(win,0,0,128,False)
		CoreWindowDrawRect(win,0,0,CoreWindowClientWidth(win)/2,CoreWindowClientHeight(win))
		CoreWindowSetColor(win,255,255,255,False)
		CoreWindowDrawText(win,s,0,0,CoreWindowClientWidth(win),CoreWindowClientHeight(win),CORE_TEXT_CENTER|CORE_TEXT_wrap)
	EndSelect
EndFunction
