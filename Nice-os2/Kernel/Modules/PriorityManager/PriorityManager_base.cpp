
// ─── Рассчитывает значение приоритета для приложения ───

// Frame_window - окно приложения, Class и Delta - значения приоритета.
// Если приоритет не будет рассчитан, эти значения меняться не должны.
VOID PriorityManager_CalculatePriorityLevel( HWND Frame_window, PLONG Class, PLONG Delta )
{
 // Для некоторых приложений надо выравнивать приоритет.
 BYTE Normalize_priority = 0;

 // Узнаем имя приложения, создавшего окно.
 CHAR Exe_name[ SIZE_OF_NAME ] = ""; GetDetectedExeName( Frame_window, Exe_name );

 // Если его удалось определить:
 if( Exe_name[ 0 ] != 0 )
  {
   // Проверяем, есть ли приложение в списке исключений.
   if( stricmpe( Exe_name, PriorityManager.Settings.PriorityNames.Exceeded_priority_1_name ) == EQUALLY ) Normalize_priority = 1;
   if( stricmpe( Exe_name, PriorityManager.Settings.PriorityNames.Exceeded_priority_2_name ) == EQUALLY ) Normalize_priority = 1;
   if( stricmpe( Exe_name, PriorityManager.Settings.PriorityNames.Exceeded_priority_3_name ) == EQUALLY ) Normalize_priority = 1;
   if( stricmpe( Exe_name, PriorityManager.Settings.PriorityNames.Exceeded_priority_4_name ) == EQUALLY ) Normalize_priority = 1;
   if( stricmpe( Exe_name, PriorityManager.Settings.PriorityNames.Exceeded_priority_5_name ) == EQUALLY ) Normalize_priority = 1;
   if( stricmpe( Exe_name, PriorityManager.Settings.PriorityNames.Exceeded_priority_6_name ) == EQUALLY ) Normalize_priority = 1;
   if( stricmpe( Exe_name, PriorityManager.Settings.PriorityNames.Exceeded_priority_7_name ) == EQUALLY ) Normalize_priority = 1;
   if( stricmpe( Exe_name, PriorityManager.Settings.PriorityNames.Exceeded_priority_8_name ) == EQUALLY ) Normalize_priority = 1;
  }

 // Узнаем окно рабочей области для окна рамки.
 HWND Client_window = WinWindowFromID( Frame_window, FID_CLIENT );

 // Если оно есть:
 if( Client_window != NULLHANDLE )
  {
   // Узнаем имя, под которым определено окно рабочей области.
   CHAR Window_name[ SIZE_OF_NAME ] = ""; WinQueryClassName( Client_window, SIZE_OF_NAME, Window_name );

   // Проверяем, есть ли окно в списке исключений.
   if( strcmp( Window_name, PriorityManager.Settings.PriorityNames.Exceeded_priority_1_name ) == EQUALLY ) Normalize_priority = 1;
   if( strcmp( Window_name, PriorityManager.Settings.PriorityNames.Exceeded_priority_2_name ) == EQUALLY ) Normalize_priority = 1;
   if( strcmp( Window_name, PriorityManager.Settings.PriorityNames.Exceeded_priority_3_name ) == EQUALLY ) Normalize_priority = 1;
   if( strcmp( Window_name, PriorityManager.Settings.PriorityNames.Exceeded_priority_4_name ) == EQUALLY ) Normalize_priority = 1;
   if( strcmp( Window_name, PriorityManager.Settings.PriorityNames.Exceeded_priority_5_name ) == EQUALLY ) Normalize_priority = 1;
   if( strcmp( Window_name, PriorityManager.Settings.PriorityNames.Exceeded_priority_6_name ) == EQUALLY ) Normalize_priority = 1;
   if( strcmp( Window_name, PriorityManager.Settings.PriorityNames.Exceeded_priority_7_name ) == EQUALLY ) Normalize_priority = 1;
   if( strcmp( Window_name, PriorityManager.Settings.PriorityNames.Exceeded_priority_8_name ) == EQUALLY ) Normalize_priority = 1;
  }

 // Задаем новые значения, если это требуется.
 // В противном случае оставляем их без изменения.
 if( Normalize_priority )
  {
   *Class = PRTYC_IDLETIME;
   *Delta = PRTYD_NORMAL;
   return;
  }

 // Возврат.
 return;
}

// ─── Заполняет упрощенный список видимых приложений в RTSettings ───

// Visible_processes - список, который надо заполнить.
VOID PriorityManager_CopyWindowListToRTSettings( VOID )
{
 // Сбрасываем все значения в списке видимых приложений.
 PriorityManager.RTSettings.Visible_processes_quantity = 0;
 bzero( PriorityManager.RTSettings.Visible_processes, sizeof( VISIBLEPROCESS ) * SIZE_OF_VISPROCLIST );

 // Узнаем список окон.
 PSWBLOCK SWBlock = NULL; QuerySwitchList( &SWBlock );

 // Переносим значения в список видимых приложений для последующего использования.
 if( SWBlock->cswentry > SIZE_OF_VISPROCLIST ) SWBlock->cswentry = SIZE_OF_VISPROCLIST;

 for( INT Count = 0; Count < SWBlock->cswentry; Count ++ )
  if( SWBlock->aswentry[ Count ].swctl.uchVisibility == SWL_VISIBLE )
   if( SWBlock->aswentry[ Count ].swctl.hwnd != NULLHANDLE )
    if( WinIsWindow( WinQueryAnchorBlock( SWBlock->aswentry[ Count ].swctl.hwnd ), SWBlock->aswentry[ Count ].swctl.hwnd ) )
     {
      PriorityManager.RTSettings.Visible_processes[ Count ].Process_ID = SWBlock->aswentry[ Count ].swctl.idProcess;
      PriorityManager.RTSettings.Visible_processes[ Count ].Frame_window = SWBlock->aswentry[ Count ].swctl.hwnd;

      PriorityManager.RTSettings.Visible_processes[ Count ].Program_type = SWBlock->aswentry[ Count ].swctl.bProgType;
      strcpy( PriorityManager.RTSettings.Visible_processes[ Count ].Title, SWBlock->aswentry[ Count ].swctl.szSwtitle );

      PriorityManager.RTSettings.Visible_processes_quantity = Count;
     }

 // Освобождаем память.
 FreeSwitchListMemory( SWBlock ); SWBlock = NULL;

 // Возврат.
 return;
}

// ─── Проставляет приоритеты всем видимым приложениям ───

// Action - действие, которое надо выполнить, Active_window - выбранное окно.
VOID PriorityManager_SetDynamicPriorityLevels( LONG Action, HWND Active_window = NULLHANDLE )
{
 // Если менять приоритеты не надо - возврат.
 if( !PriorityManager.Settings.Dynamic_priority ) return;

 // Узнаем список видимых приложений.
 PriorityManager_CopyWindowListToRTSettings();

 // Узнаем приложение, которое сейчас выбрано.
 PID Active_process = 0;

 if( Action == SDPL_FORCE_ACTIVE_PROCESS || Action == SDPL_SUPPRESS_ACTIVE_PROCESS )
  {
   // Узнаем окно, которое сейчас выбрано.
   if( Active_window == NULLHANDLE ) Active_window = WinQueryActiveWindow( QueryDesktopWindow() );

   // Если оно есть:
   if( Active_window != NULLHANDLE )
    {
     // Узнаем приложение, которое сейчас выбрано.
     Active_process = QueryWindowRealProcessID( Active_window );
    }
  }

 // Если надо рассчитать приоритеты для всех приложений:
 if( Action == SDPL_FORCE_ACTIVE_PROCESS && Active_process != 0 )
  {
   // Назначаем низкий приоритет всем приложениям.
   // Это значение останется для невидимых приложений.
   for( INT Count = 0; Count < SIZE_OF_VISPROCLIST; Count ++ )
    {
     // Если запись ничего не содержит - продолжаем просмотр списка.
     if( PriorityManager.RTSettings.Visible_processes[ Count ].Process_ID == 0 ) continue;

     // Ставим приоритет.
     PriorityManager.RTSettings.Visible_processes[ Count ].Priority_class = PRTYC_IDLETIME;
     PriorityManager.RTSettings.Visible_processes[ Count ].Priority_delta = PRTYD_NORMAL;
    }

   // Задаем полноэкранным приложениям средний приоритет.
   for( Count = 0; Count < SIZE_OF_VISPROCLIST; Count ++ )
    {
     // Если запись ничего не содержит - продолжаем просмотр списка.
     if( PriorityManager.RTSettings.Visible_processes[ Count ].Process_ID == 0 ) continue;

     // Если приложение идет в полный экран - назначаем ему средний приоритет.
     if( PriorityManager.RTSettings.Visible_processes[ Count ].Program_type == PROG_FULLSCREEN )
      {
       // Рассчитываем приоритет для приложения.
       LONG Class = PRTYC_IDLETIME;
       LONG Delta = PRTYD_MAXIMUM;

       if( PriorityManager.Settings.Normalize_priority ) PriorityManager_CalculatePriorityLevel( PriorityManager.RTSettings.Visible_processes[ Count ].Frame_window, &Class, &Delta );

       // Меняем его свойства в списке.
       PriorityManager.RTSettings.Visible_processes[ Count ].Priority_class = Class;
       PriorityManager.RTSettings.Visible_processes[ Count ].Priority_delta = Delta;
      }
    }

   // Задаем приложениям, имеющим видимые окна, хороший приоритет.
   for( Count = 0; Count < SIZE_OF_VISPROCLIST; Count ++ )
    {
     // Если запись ничего не содержит - продолжаем просмотр списка.
     if( PriorityManager.RTSettings.Visible_processes[ Count ].Process_ID == 0 ) continue;

     // Если окно видимо - ставим приложению хороший приоритет.
     if( WinIsWindowShowing( PriorityManager.RTSettings.Visible_processes[ Count ].Frame_window ) )
      {
       // Узнаем приложение, создавшее это окно.
       PID Inactive_process = PriorityManager.RTSettings.Visible_processes[ Count ].Process_ID;

       // Рассчитываем приоритет для приложения.
       LONG Class = PRTYC_REGULAR;
       LONG Delta = PRTYD_MINIMUM;

       if( PriorityManager.Settings.Normalize_priority ) PriorityManager_CalculatePriorityLevel( PriorityManager.RTSettings.Visible_processes[ Count ].Frame_window, &Class, &Delta );

       // Меняем его свойства в списке.
       for( INT Pointer = 0; Pointer < SIZE_OF_VISPROCLIST; Pointer ++ )
        if( PriorityManager.RTSettings.Visible_processes[ Pointer ].Process_ID == Inactive_process )
         {
          PriorityManager.RTSettings.Visible_processes[ Pointer ].Priority_class = Class;
          PriorityManager.RTSettings.Visible_processes[ Pointer ].Priority_delta = Delta;
         }
      }
    }

   // Задаем высокий приоритет приложению, с которым работает пользователь.
   LONG Class = PRTYC_REGULAR;
   LONG Delta = PRTYD_NORMAL;

   if( PriorityManager.Settings.Normalize_priority ) PriorityManager_CalculatePriorityLevel( Active_window, &Class, &Delta );

   // Меняем его свойства в списке.
   for( INT Pointer = 0; Pointer < SIZE_OF_VISPROCLIST; Pointer ++ )
    if( PriorityManager.RTSettings.Visible_processes[ Pointer ].Process_ID == Active_process )
     {
      PriorityManager.RTSettings.Visible_processes[ Pointer ].Priority_class = Class;
      PriorityManager.RTSettings.Visible_processes[ Pointer ].Priority_delta = Delta;
     }
  }

 // Если надо снизить приоритет одного приложения:
 if( Action == SDPL_SUPPRESS_ACTIVE_PROCESS && Active_process != 0 )
  {
   // Задаем приложению низкий приоритет. Остальные приложения не трогаем.
   for( INT Count = 0; Count < SIZE_OF_VISPROCLIST; Count ++ )
    {
     // Если запись ничего не содержит - продолжаем просмотр списка.
     if( PriorityManager.RTSettings.Visible_processes[ Count ].Process_ID == 0 ) continue;

     // Ставим приоритет выбранному приложению.
     if( PriorityManager.RTSettings.Visible_processes[ Count ].Process_ID == Active_process )
      {
       PriorityManager.RTSettings.Visible_processes[ Count ].Priority_class = PRTYC_REGULAR;
       PriorityManager.RTSettings.Visible_processes[ Count ].Priority_delta = PRTYD_MINIMUM;
      }
     // Удаляем из списка остальные приложения.
     else
      {
       PriorityManager.RTSettings.Visible_processes[ Count ].Process_ID = 0;
      }
    }
  }

 // Если надо задать всем приложениям низкий приоритет:
 if( Action == SDPL_SUPPRESS_ALL_PROCESSES )
  {
   // Задаем всем приложениям низкий приоритет.
   for( INT Count = 0; Count < SIZE_OF_VISPROCLIST; Count ++ )
    {
     // Если запись ничего не содержит - продолжаем просмотр списка.
     if( PriorityManager.RTSettings.Visible_processes[ Count ].Process_ID == 0 ) continue;

     // Ставим приоритет.
     PriorityManager.RTSettings.Visible_processes[ Count ].Priority_class = PRTYC_REGULAR;
     PriorityManager.RTSettings.Visible_processes[ Count ].Priority_delta = PRTYD_MINIMUM;
    }
  }

 // Если надо задать всем приложениям обычный приоритет:
 if( Action == SDPL_RESTORE_ALL_PROCESSES )
  {
   // Задаем всем приложениям обычный приоритет.
   for( INT Count = 0; Count < SIZE_OF_VISPROCLIST; Count ++ )
    {
     // Если запись ничего не содержит - продолжаем просмотр списка.
     if( PriorityManager.RTSettings.Visible_processes[ Count ].Process_ID == 0 ) continue;

     // Ставим приоритет.
     PriorityManager.RTSettings.Visible_processes[ Count ].Priority_class = PRTYC_REGULAR;
     PriorityManager.RTSettings.Visible_processes[ Count ].Priority_delta = PRTYD_NORMAL;
    }
  }

 // Выбрасываем приложения, которые трогать не надо.
 for( INT Count = 0; Count < SIZE_OF_VISPROCLIST; Count ++ )
  {
   // Если запись ничего не содержит - продолжаем просмотр списка.
   if( PriorityManager.RTSettings.Visible_processes[ Count ].Process_ID == 0 ) continue;

   // Если менять приоритет нельзя - удаляем все записи для этого приложения.
   if( !PriorityManager_PermissionForPriorityActions( PriorityManager.RTSettings.Visible_processes[ Count ].Frame_window ) ||
       !PriorityManager_PermissionForDynamicPriorityActions( PriorityManager.RTSettings.Visible_processes[ Count ].Frame_window, PriorityManager.RTSettings.Visible_processes[ Count ].Title ) )
    {
     // Узнаем приложение, которое нельзя трогать.
     PID Excepted_process = PriorityManager.RTSettings.Visible_processes[ Count ].Process_ID;

     // Удаляем его из списка.
     for( INT Pointer = 0; Pointer < SIZE_OF_VISPROCLIST; Pointer ++ )
      if( PriorityManager.RTSettings.Visible_processes[ Pointer ].Process_ID == Excepted_process )
       PriorityManager.RTSettings.Visible_processes[ Pointer ].Process_ID = 0;
    }
  }

 // Выбрасываем повторы.
 for( Count = 0; Count < SIZE_OF_VISPROCLIST; Count ++ )
  {
   // Если запись ничего не содержит - продолжаем просмотр списка.
   if( PriorityManager.RTSettings.Visible_processes[ Count ].Process_ID == 0 ) continue;

   // Выбрасываем повторы.
   for( INT Pointer = 0; Pointer < SIZE_OF_VISPROCLIST; Pointer ++ )
    if( Pointer != Count )
     if( PriorityManager.RTSettings.Visible_processes[ Pointer ].Process_ID == PriorityManager.RTSettings.Visible_processes[ Count ].Process_ID )
      PriorityManager.RTSettings.Visible_processes[ Pointer ].Process_ID = 0;
  }

 // Устанавливаем приоритеты для текстовых приложений.
 for( Count = 0; Count < SIZE_OF_VISPROCLIST; Count ++ )
  {
   // Если запись ничего не содержит - продолжаем просмотр списка.
   if( PriorityManager.RTSettings.Visible_processes[ Count ].Process_ID == 0 ) continue;

   // Если это текстовое приложение:
   if( PriorityManager.RTSettings.Visible_processes[ Count ].Program_type == PROG_FULLSCREEN ||
       PriorityManager.RTSettings.Visible_processes[ Count ].Program_type == PROG_WINDOWABLEVIO )
    {
     // Устанавливаем приоритет.
     SetPriorityLevel( PriorityManager.RTSettings.Visible_processes[ Count ].Frame_window, PriorityManager.RTSettings.Visible_processes[ Count ].Priority_class, PriorityManager.RTSettings.Visible_processes[ Count ].Priority_delta );

     // Выбрасываем приложение из списка.
     PriorityManager.RTSettings.Visible_processes[ Count ].Process_ID = 0;
    }
  }

 // Устанавливаем приоритеты для оконных приложений.
 for( Count = 0; Count < SIZE_OF_VISPROCLIST; Count ++ )
  {
   // Если запись ничего не содержит - продолжаем просмотр списка.
   if( PriorityManager.RTSettings.Visible_processes[ Count ].Process_ID == 0 ) continue;

   // Устанавливаем приоритет.
   SetPriorityLevel( PriorityManager.RTSettings.Visible_processes[ Count ].Frame_window, PriorityManager.RTSettings.Visible_processes[ Count ].Priority_class, PriorityManager.RTSettings.Visible_processes[ Count ].Priority_delta );
  }

 // Возврат.
 return;
}
