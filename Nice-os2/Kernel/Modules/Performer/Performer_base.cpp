
// ─── Требует отключения выравнивания окон ───

// State - разрешение или запрещение выравнивания окон.
VOID Performer_DisableArranger( BYTE State )
{
 // Запоминаем значение.
 Performer.RTSettings.Performer_disables_arranger = State;

 // Возврат.
 return;
}

// ─── Возвращает в обычное состояние окно, которое убрано наверх ───

// Все переменные - внешние.
VOID Performer_UnrollWindow( HWND Frame_window )
{
 // Если окно на самом деле не убрано наверх - возврат.
 if( Frame_window != RolledWindow() ) return;

 // Отключаем выравнивание окон.
 Performer_DisableArranger( 1 );

 // Возвращаем окно в обычное состояние.
 INT X = 0; INT Y = 0; INT Width = 0; INT Height = 0;
 GetRolledWindowPlacement( &X, &Y, &Width, &Height );

 WinSetWindowPos( Frame_window, NULLHANDLE, X, Y, Width, Height, SWP_SIZE | SWP_MOVE | SWP_NOADJUST );

 // Включаем выравнивание окон.
 Performer_DisableArranger( 0 );

 // Перерисовываем рамку окна. Посылаем сообщение в поток рисования.
 WinPostQueueMsg( Enhancer.Modules.Painter->Message_queue, SM_DRAW_FRAME, (MPARAM) Frame_window, (MPARAM) WT_UNKNOWN );

 // Окно - неизвестно.
 RememberRolledWindow( NULLHANDLE );

 // Возврат.
 return;
}

