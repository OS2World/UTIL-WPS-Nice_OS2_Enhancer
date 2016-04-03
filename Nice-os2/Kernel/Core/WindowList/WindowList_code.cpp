
// ─── Делает окно доступным или недоступным для переключения по Alt+Tab ───

// Frame_window - окно рамки, Flag - значение.
VOID Krnl_WindowList_SetJumpableFlag( HWND Frame_window, ULONG Flag )
{
 // Узнаем, есть ли окно в списке окон.
 HSWITCH Switch_handle = WinQuerySwitchHandle( Frame_window, NULLHANDLE );

 // Если оно есть:
 if( Switch_handle != NULLHANDLE )
  {
   // Узнаем свойства окна.
   SWCNTRL Task = {0}; WinQuerySwitchEntry( Switch_handle, &Task );

   // Если они были получены:
   if( Task.hwnd != NULLHANDLE )
    {
     // Если окно недоступно в списке окон - ничего делать не надо.
     if( Task.uchVisibility != SWL_VISIBLE ) return;

     // Меняем свойства.
     if( Task.fbJump != Flag )
      {
       Task.fbJump = Flag;
       WinChangeSwitchEntry( Switch_handle, &Task );
      }
    }
  }

 // Возврат.
 return;
}

// ─── Делает все окна приложения доступными или недоступными для переключения ───

// WinList_title - название в списке окон, Flag - значение.
VOID Krnl_WindowList_SetProcessJumpableFlag( PCHAR WinList_title, ULONG Flag )
{
 // Перебираем окна в окне рабочего стола.
 HENUM Enumeration = WinBeginEnumWindows( QueryDesktopWindow() ); HWND Window = NULLHANDLE;
 while( ( Window = WinGetNextWindow( Enumeration ) ) != NULLHANDLE )
  {
   // Узнаем свойства окна.
   HSWITCH Switch_handle = WinQuerySwitchHandle( Window, NULLHANDLE );
   SWCNTRL Task = {0}; WinQuerySwitchEntry( Switch_handle, &Task );

   // Если они были получены:
   if( Task.hwnd != NULLHANDLE )
    {
     // Если окно недоступно в списке окон - ничего делать не надо.
     if( Task.uchVisibility != SWL_VISIBLE ) continue;

     // Если заголовок окна неизвестен или окно было создано другим приложением - ничего делать не надо.
     if( Task.szSwtitle == NULL || !stristr( WinList_title, Task.szSwtitle ) ) continue;

     // Меняем свойства.
     if( Task.fbJump != Flag )
      {
       Task.fbJump = Flag;
       WinChangeSwitchEntry( Switch_handle, &Task );
      }
    }
  }
 WinEndEnumWindows( Enumeration );

 // Возврат.
 return;
}

// ─── Узнает, доступно ли окно для переключения по Alt+Tab ───

// Frame_window - окно рамки.
ULONG Krnl_WindowList_WindowIsJumpable( HWND Frame_window )
{
 // Узнаем, есть ли окно в списке окон.
 HSWITCH Switch_handle = WinQuerySwitchHandle( Frame_window, NULLHANDLE );

 // Если оно есть:
 if( Switch_handle != NULLHANDLE )
  {
   // Узнаем свойства окна.
   SWCNTRL Task = {0}; WinQuerySwitchEntry( Switch_handle, &Task );

   // Если они были получены:
   if( Task.hwnd != NULLHANDLE )
    {
     // Расширитель не должен переключаться в полноэкранные приложения.
     if( Task.bProgType == PROG_FULLSCREEN || Task.bProgType == PROG_VDM ) return 0;

     // Возвращаем значение.
     if( Task.fbJump == SWL_JUMPABLE ) return 1;
    }
  }

 // Возврат.
 return 0;
}

// ─── Узнает, доступно ли окно для переключения из списка окон ───

// Frame_window - окно рамки.
ULONG Krnl_WindowList_WindowIsTouchable( HWND Frame_window )
{
 // Узнаем, есть ли окно в списке окон.
 HSWITCH Switch_handle = WinQuerySwitchHandle( Frame_window, NULLHANDLE );

 // Если оно есть:
 if( Switch_handle != NULLHANDLE )
  {
   // Узнаем свойства окна.
   SWCNTRL Task = {0}; WinQuerySwitchEntry( Switch_handle, &Task );

   // Если они были получены:
   if( Task.hwnd != NULLHANDLE )
    {
     // Расширитель не должен переключаться в полноэкранные приложения.
     if( Task.bProgType == PROG_FULLSCREEN || Task.bProgType == PROG_VDM ) return 0;

     // Возвращаем значение.
     if( Task.uchVisibility == SWL_VISIBLE ) return 1;
    }
  }

 // Возврат.
 return 0;
}

// ─── Делает все окна доступными для переключения ───

// Desktop - окно рабочего стола.
VOID Krnl_WindowList_SetAllWindowsJumpable( HWND Desktop )
{
 // Перебираем окна в окне рабочего стола.
 HENUM Enumeration = WinBeginEnumWindows( Desktop ); HWND Window = NULLHANDLE;
 while( ( Window = WinGetNextWindow( Enumeration ) ) != NULLHANDLE )
  {
   // Устанавливаем свойство.
   if( !Krnl_WindowList_WindowIsJumpable( Window ) ) Krnl_WindowList_SetJumpableFlag( Window, SWL_JUMPABLE );
  }
 WinEndEnumWindows( Enumeration );

 // Возврат.
 return;
}

// ─── Находит окно в списке окон ───

// WinList_title - название в списке окон.
HWND Krnl_WindowList_FindFrameWindowInWindowList( PCHAR WinList_title )
{
 // Окно может быть не найдено.
 HWND Frame_window = NULLHANDLE;

 {
  // Перебираем окна в окне рабочего стола.
  HENUM Enumeration = WinBeginEnumWindows( QueryDesktopWindow() ); HWND Window = NULLHANDLE;
  while( ( Window = WinGetNextWindow( Enumeration ) ) != NULLHANDLE )
   {
    // Узнаем свойства окна.
    HSWITCH Switch_handle = WinQuerySwitchHandle( Window, NULLHANDLE );
    SWCNTRL Task = {0}; WinQuerySwitchEntry( Switch_handle, &Task );

    // Если они были получены:
    if( Task.hwnd != NULLHANDLE )
     {
      // Если окно недоступно в списке окон - ничего делать не надо.
      if( Task.uchVisibility != SWL_VISIBLE ) continue;

      // Если заголовок окна неизвестен - ничего делать не надо.
      if( Task.szSwtitle == NULL ) continue;

      // Если заголовок содержит искомую строку:
      if( stristr( WinList_title, Task.szSwtitle ) )
       {
        // Запоминаем окно.
        Frame_window = QueryFrameWindow( Window );

        // Прекращаем перебор окон.
        break;
       }
     }
   }
  WinEndEnumWindows( Enumeration );
 }

 // Возврат.
 return Frame_window;
}

