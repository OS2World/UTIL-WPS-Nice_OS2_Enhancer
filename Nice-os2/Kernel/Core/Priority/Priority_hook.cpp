
// ─── Слежение за сообщениями ───

// Все переменные - внешние.
VOID PriorityInputHook( PQMSG Message )
{
 // Устанавливаем приоритет приложения.
 // Это сообщение посылается расширителем в окно рабочего стола, так как из него можно менять приоритеты всех приложений.
 if( Message->hwnd == NULLHANDLE ) if( Message->msg == WM_MARK )
  if( Message->mp1 == (MPARAM) MRK_SET_PRIORITY )
   {
    // Узнаем требуемые значения приоритетов.
    HWND Frame_window = (HWND) Message->mp2;

    LONG Class = PRTYC_NOCHANGE; FindProperty( Frame_window, PRP_PRIORITY_CLASS, &Class );
    LONG Delta = PRTYD_NORMAL;   FindProperty( Frame_window, PRP_PRIORITY_DELTA, &Delta );

    // Если они заданы:
    if( Class != PRTYC_NOCHANGE )
     {
      // Узнаем приложение, создавшее окно.
      PID Process_ID = QueryWindowRealProcessID( Frame_window );

      // Если оно известно - изменяем приоритет.
      if( Process_ID != 0 ) DosSetPriority( PRTYS_PROCESSTREE, Class, Delta, Process_ID );

      // Сбрасываем значения.
      Class = PRTYC_NOCHANGE; SetProperty( Frame_window, PRP_PRIORITY_CLASS, &Class );
      Delta = PRTYD_NORMAL;   SetProperty( Frame_window, PRP_PRIORITY_DELTA, &Delta );
     }
   }

 // Возврат.
 return;
}
