
// ─── Слежение за сообщениями ───

// Все переменные - внешние.
VOID VIOFontManagerInputHook( HAB Application, PQMSG Message, PBYTE Discarding )
{
 // Меняем шрифты для текстовых окон.
 if( VIOFontManager.Settings.Change_VIO_font_metrics )
  {
   // Устанавливаем шрифт в окне.
   if( Message->msg == WM_MARK ) if( Message->mp1 == (MPARAM) MRK_SET_VIO_FONT )
    {
     // Узнаем окно рамки.
     HWND Frame_window = (HWND) Message->mp2;

     // Посылаем сообщение в поток.
     WinPostQueueMsg( Enhancer.Modules.Changer->Message_queue, SM_APPLY_VIO_FONT, (MPARAM) Frame_window, 0 );
    }

   // Делаем окно видимым и выравниваем его по середине экрана.
   if( Message->msg == WM_MARK ) if( Message->mp1 == (MPARAM) MRK_SHOW_AND_ARRANGE )
    {
     // Посылаем сообщение в поток.
     HWND Frame_window = (HWND) Message->mp2;
     WinPostQueueMsg( Enhancer.Modules.Changer->Message_queue, SM_SHOW_AND_ARRANGE, (MPARAM) Frame_window, 0 );
    }
  }

 // Возврат.
 return;
}

// ─── Слежение за сообщениями ───

// Все переменные - внешние.
VOID VIOFontManagerSendMsgHook( HAB Application, PSMHSTRUCT Message )
{
 // Меняем шрифты для текстовых окон.
 if( VIOFontManager.Settings.Change_VIO_font_metrics ) if( !RoomsChangeIsInProcess() )
  {
   // Если окно рамки становится видимым:
   if( TopFrameWindowIsShowing( Message ) )
    {
     // Узнаем окно рамки.
     HWND Frame_window = QueryFrameWindow( Message->hwnd );

     // Если это текстовое окно:
     if( IsVIOWindow( Frame_window ) )
      {
       // Узнаем имя приложения, создавшего окно.
       CHAR Exe_name[ SIZE_OF_NAME ] = ""; GetDetectedExeName( Frame_window, Exe_name );

       // Если его удалось определить:
       if( Exe_name[ 0 ] != 0 )
        {
         // Если в окне надо менять шрифт - посылаем сообщение в поток, который это сделает.
         if( VIOFontManager_VIOFontMustBeChanged( Frame_window ) )
          WinPostQueueMsg( Enhancer.Modules.Changer->Message_queue, SM_CHANGE_VIO_FONT, (MPARAM) Frame_window, 0 );
        }
       // А если оно неизвестно - посылаем сообщение в поток, который подождет его некоторое время.
       else
        {
         WinPostQueueMsg( Enhancer.Modules.VIOMonitor->Message_queue, SM_MONITOR_VIO, (MPARAM) Frame_window, (MPARAM) SM_CHANGE_VIO_FONT );
        }
      }
    }
  }

 // Возврат.
 return;
}
