
// ─── Обновляет окно ───

// Frame_window - окно, которое надо обновить.
VOID Repaint_UpdateWindow( HWND Frame_window )
{
 // Заголовок окна, кнопки и так далее должны быть перерисованы.
 // Указывать лишние флажки "FCF_*" в этом сообщении нельзя - окно рамки ничего не будет делать.
 WinPostMsg( Frame_window, WM_UPDATEFRAME, MPFROMP( FCF_SYSMENU | FCF_TITLEBAR | FCF_MAXBUTTON | FCF_MINBUTTON | FCF_HIDEBUTTON | FCF_MENU ), 0 );

 // Все окно должно быть перерисовано.
 WinInvalidateRect( Frame_window, NULL, 1 );

 // Возврат.
 return;
}

// ─── Обновляет рамку окна, задавая правильную ширину ───

// Frame_window - окно, которое надо обновить.
VOID Repaint_UpdateFrameBorder( HWND Frame_window )
{
 // Если окно имеет обычную рамку:
 if( FrameType( Frame_window ) == FT_NORMAL )
  {
   // Узнаем окно рабочего стола.
   HWND Desktop = QueryDesktopWindow();

   // Узнаем ширину рамки по умолчанию.
   INT Normal_frame = Min( WinQuerySysValue( Desktop, SV_CXSIZEBORDER ), WinQuerySysValue( Desktop, SV_CYSIZEBORDER ) );

   // Посылаем сообщение в окно.
   WinPostMsg( Frame_window, WM_SETBORDERSIZE, (MPARAM) Normal_frame, (MPARAM) Normal_frame );
  }

 // Возврат.
 return;
}

// ─── Обновляет все окна ───

// Parent_window - родительское окно или окно рабочего стола.
// Во время работы возможен повторный вызов, при этом Recursive_calling != 0.
VOID Repaint_UpdateAllWindows( HWND Parent_window, BYTE Recursive_calling = 0 )
{
 // Если окна будут обновлены - надо сделать задержку.
 BYTE Do_retard = 0;

 // Узнаем окно оболочки.
 HWND Shell_window = GetDetectedShellWindow();

 // Перебираем окна.
 HENUM Enumeration = WinBeginEnumWindows( Parent_window ); HWND Window = NULLHANDLE;
 while( ( Window = WinGetNextWindow( Enumeration ) ) != NULLHANDLE )
  {
   // Если это окно оболочки - продолжаем перебор окон.
   if( Window == Shell_window ) continue;

   // Если это не окно рамки - продолжаем перебор окон.
   if( !IsFrameWindow( Window ) ) continue;

   // Если это окно рамки списка окон - его свойства надо узнать заранее.
   if( IsWinListWindow( Window ) )
    {
     // Посылаем сообщение в поток.
     WinPostQueueMsg( Enhancer.Modules.Diver->Message_queue, SM_QUERY_PROPERTIES, (MPARAM) Window, (MPARAM) WT_UNKNOWN );
    }

   // Задаем размер рамки окна.
   Repaint_UpdateFrameBorder( Window );

   // Если окно скрыто - продолжаем перебор окон.
   if( !WinIsWindowVisible( Window ) ) continue;

   // Обновляем окно.
   Repaint_UpdateWindow( Window );

   // Если это не повторный вызов:
   if( !Recursive_calling )
    {
     // В окне рабочей области могут быть расположены другие окна рамок. Перебираем их тоже.
     HWND Client_window = WinWindowFromID( Window, FID_CLIENT );
     if( Client_window != NULLHANDLE ) Repaint_UpdateAllWindows( Client_window, RECURSIVE_CALLING );

     // Надо будет выполнить задержку.
     Do_retard = 1;
    }
  }
 WinEndEnumWindows( Enumeration );

 // Ждем некоторое время, если это требуется.
 if( Do_retard ) Retard();

 // Возврат.
 return;
}
