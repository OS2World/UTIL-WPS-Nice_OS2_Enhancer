
// ─── Проверяет, можно ли менять приоритет приложения ───

// Frame_window - окно рамки.
// Возвращаемое значение: 1, если можно, 0, если нельзя.
BYTE PriorityManager_PermissionForPriorityActions( HWND Frame_window )
{
 // Если окно создано оболочкой или расширителем - менять приоритет нельзя.
 if( IsPMShellAuxiliaryWindow( Frame_window ) ||
     IsWorkplaceShellWindow( Frame_window ) ||
     WindowIsCreatedBy( APP_NICE, Frame_window ) ) return 0;

 // Узнаем имя приложения, создавшего окно.
 CHAR Exe_name[ SIZE_OF_NAME ] = ""; GetDetectedExeName( Frame_window, Exe_name );

 // Если удалось определить имя приложения:
 if( Exe_name[ 0 ] != 0 )
  {
   // Если это другой расширитель - менять приоритет нельзя.
   if( WindowIsCreatedBy( APP_NPSWPS, Frame_window ) ) return 0;

   // Если это прибиватель повисших задач - менять приоритет нельзя.
   if( WindowIsCreatedBy( APP_WATCHCAT, Frame_window ) ) return 0;

   // Если приложение требует времени для работы - менять приоритет нельзя.
   if( WindowIsCreatedBy( APP_ZMP3, Frame_window ) ) return 0;
   if( WindowIsCreatedBy( APP_TIMIDITY, Frame_window ) ) return 0;

   if( WindowIsCreatedBy( APP_CDRECORD, Frame_window ) ) return 0;
   if( WindowIsCreatedBy( APP_DVDRECORD, Frame_window ) ) return 0;

   // Даже если VirtualPC забирает все время, менять приоритет нельзя.
   if( WindowIsCreatedBy( APP_VIRTUALPC, Frame_window ) ) return 0;
  }

 // Если это текстовое окно и его трогать не надо - менять приоритет нельзя.
 if( !PriorityManager.Settings.Dynamic_priority_for_VIO ) if( IsVIOWindow( Frame_window ) ) return 0;

 // Если это окно списка окон - менять приоритет нельзя (на случай, если не сработают условия вначале).
 if( IsWinListWindow( Frame_window ) ) return 0;

 // Возврат.
 return 1;
}

// ─── Проверяет, можно ли менять приоритет приложения ───

// Frame_window - окно рамки, WinList_title - название в списке окон.
// Возвращаемое значение: 1, если можно, 0, если нельзя.
BYTE PriorityManager_PermissionForDynamicPriorityActions( HWND Frame_window, PCHAR WinList_title = NULL )
{
 // Если окно должно быть удалено из списка окон - менять приоритет нельзя.
 if( WinList_title != NULL ) if( WindowWillBeHidden( WinList_title ) ) return 0;

 // Если окно недоступно - менять приоритет нельзя.
 if( !FrameWindowIsAccessible( Frame_window ) ) return 0;

 // Возврат.
 return 1;
}
