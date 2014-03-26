
// ─── Слежение за сообщениями ───

// Все переменные - внешние.
VOID PriorityManagerInputHook( HAB Application, PQMSG Message, PBYTE Discarding )
{
 // Снижаем приоритеты приложений при закрытии окон.
 if( PriorityManager.Settings.Dynamic_priority )
  {
   // Если окно закрывается:
   if( FrameWindowIsClosing( Message ) )
    {
     // Узнаем окно рамки.
     HWND Frame_window = QueryFrameWindow( Message->hwnd );

     // Если в него можно переключиться из списка окон:
     if( WindowIsTouchable( Frame_window ) )
      {
       // Если родительское окно - рабочий стол:
       if( WinQueryWindow( Frame_window, QW_PARENT ) == QueryDesktopWindow() )
        {
         // Устанавливаем приложению наименьший приоритет.
         PriorityManager_SetDynamicPriorityLevels( SDPL_SUPPRESS_ACTIVE_PROCESS, Frame_window );
        }
      }
    }
  }

 // Возврат.
 return;
}

// ─── Слежение за сообщениями ───

// Все переменные - внешние.
VOID PriorityManagerSendMsgHook( HAB Application, PSMHSTRUCT Message )
{
 // Меняем приоритеты приложений при переключении между окнами.
 if( PriorityManager.Settings.Normalize_priority || PriorityManager.Settings.Dynamic_priority ) if( !RoomsChangeIsInProcess() )
  {
   // Если окно рамки становится выбранным:
   if( TopFrameWindowIsActivating( Message ) )
    {
     // Узнаем окно рамки.
     HWND Frame_window = QueryFrameWindow( Message->hwnd );

     // Устанавливаем значения приоритетов.
     BYTE Priority_is_changed = 0;

     // Если надо ставить приоритеты для всех приложений:
     if( PriorityManager.Settings.Dynamic_priority )
      {
       // Устанавливаем их.
       PriorityManager_SetDynamicPriorityLevels( SDPL_FORCE_ACTIVE_PROCESS, Frame_window );

       // Запоминаем, что это сделано.
       Priority_is_changed = 1;
      }

     // А если этого делать не надо - можно менять приоритеты для приложений, указанных пользователем.
     if( !Priority_is_changed ) if( PriorityManager.Settings.Normalize_priority )
      if( PriorityManager_PermissionForPriorityActions( Frame_window ) )
       {
        // Рассчитываем приоритет для приложения.
        LONG Class = PRTYC_NOCHANGE;
        LONG Delta = PRTYD_INFINITY;

        PriorityManager_CalculatePriorityLevel( Frame_window, &Class, &Delta );

        // Изменяем его, если это требуется.
        if( Class != PRTYC_NOCHANGE && Delta != PRTYD_INFINITY ) SetPriorityLevel( Frame_window, Class, Delta );
       }
    }
  }

 // Снижаем приоритет приложению, которое перестает быть выбранным.
 // Это делается еще до того, как выбранным станет другое приложение.
 if( PriorityManager.Settings.Dynamic_priority )
  if( !RoomsChangeIsInProcess() ) if( TopFrameWindowIsInactivating( Message ) )
   {
    // Устанавливаем приложению наименьший приоритет.
    HWND Frame_window = QueryFrameWindow( Message->hwnd );
    PriorityManager_SetDynamicPriorityLevels( SDPL_SUPPRESS_ACTIVE_PROCESS, Frame_window );
   }

 // Возврат.
 return;
}
