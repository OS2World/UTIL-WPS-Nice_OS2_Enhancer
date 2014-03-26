
// ─── Слежение за сообщениями ───

// Все переменные - внешние.
VOID ApplierInputHook( HAB Application, PQMSG Message, PBYTE Discarding )
{
 // Если надо выполнять действия с окнами диалогов:
 if( Applier.Settings.Script_after_Logon || Applier.Settings.Remember_dialog_fields || Applier.Settings.Send_Yes )
  {
   // Запоминаем окна ввода пароля. Это сообщение посылается в окно в SendMsgHook() при обработке другого сообщения.
   if( Applier.Settings.Script_after_Logon )
    if( Message->msg == WM_MARK ) if( Message->mp1 == (MPARAM) MRK_LOGON_WINDOW )
     {
      // Посылаем сообщение в поток.
      HWND Frame_window = (HWND) Message->mp2;
      WinPostQueueMsg( Enhancer.Modules.Applier->Message_queue, SM_LOGON_WINDOW, (MPARAM) Frame_window, 0 );
     }

   // Запоминаем значения в окнах ввода пароля. Это сообщение посылается в окно в SendMsgHook() при обработке другого сообщения.
   if( Applier.Settings.Script_after_Logon )
    if( Message->msg == WM_MARK ) if( Message->mp1 == (MPARAM) MRK_LOGON_VALUES )
     {
      // Посылаем сообщение в поток.
      HWND Frame_window = (HWND) Message->mp2;
      WinPostQueueMsg( Enhancer.Modules.Applier->Message_queue, SM_LOGON_VALUES, (MPARAM) Frame_window, 0 );
     }

   // Восстанавливаем поля ввода в окнах диалогов. Это сообщение посылается в окно в SendMsgHook() при обработке другого сообщения.
   if( Applier.Settings.Remember_dialog_fields )
    if( Message->msg == WM_MARK ) if( Message->mp1 == (MPARAM) MRK_COMPLETE_DIALOG )
     {
      // Посылаем сообщение в поток.
      HWND Frame_window = (HWND) Message->mp2;
      WinPostQueueMsg( Enhancer.Modules.Applier->Message_queue, SM_COMPLETE_DIALOG, (MPARAM) Frame_window, 0 );
     }

   // Закрываем окна диалогов. Это сообщение посылается в окно в SendMsgHook() при обработке другого сообщения.
   if( Applier.Settings.Send_Yes )
    if( Message->msg == WM_MARK ) if( Message->mp1 == (MPARAM) MRK_SEND_YES )
     {
      // Посылаем сообщение в поток.
      HWND Frame_window = (HWND) Message->mp2;
      WinPostQueueMsg( Enhancer.Modules.Applier->Message_queue, SM_SEND_YES, (MPARAM) Frame_window, 0 );
     }
  }

 // Возврат.
 return;
}

// ─── Слежение за сообщениями от клавиатуры ───

// Все переменные - внешние.
VOID ApplierKbdInputHook( HAB Application, PQMSG Message, PBYTE Discarding )
{
 // Запоминаем значения в окне ввода пароля.
 if( Applier.Settings.Script_after_Logon ) if( Applier.RTSettings.Logon_in_process )
  {
   // Следим за нажатиями на клавиши.
   if( Message->msg == WM_CHAR )
    {
     // Смотрим, какая клавиша нажата.
     BYTE Scan_code = CHAR4FROMMP( Message->mp1 );
     SHORT State = SHORT1FROMMP( Message->mp1 );

     // Если идет отжатие клавиши:
     if( State & KC_KEYUP )
      {
       // Проверяем клавишу.
       BYTE Latin_key = 0;

       if( Scan_code != 0 )
        if( !( State & KC_CTRL ) ) if( !( State & KC_ALT ) )
         Latin_key = 1;

       // Если это латинская клавиша:
       if( Latin_key )
        {
         // Узнаем окно рамки.
         HWND Frame_window = QueryFrameWindow( Message->hwnd );

         // Если оно есть в списке отслеживаемых окон:
         for( INT Count = APPLIER_MONITORING_LOGON_WINDOWS - 1; Count >= 0; Count -- )
          if( Applier.RTDlgMemory.Logon_windows[ Count ].Window == Frame_window )
           {
            // Посылаем в очередь сообщение WM_MARK. Когда оно будет получено, окно подготовит значение в поле ввода.
            HMQ Message_queue = WinQueryWindowULong( Frame_window, QWL_HMQ );
            WinPostQueueMsg( Message_queue, WM_MARK, (MPARAM) MRK_LOGON_VALUES, (MPARAM) Frame_window );
            break;
           }
        }
      }
    }
  }

 // Возврат.
 return;
}

// ─── Слежение за сообщениями ───

// Все переменные - внешние.
VOID ApplierSendMsgHook( HAB Application, PSMHSTRUCT Message )
{
 // Если надо выполнять действия с окнами диалогов:
 if( Applier.Settings.Script_after_Logon || Applier.Settings.Remember_dialog_fields || Applier.Settings.Send_Yes ) if( !RoomsChangeIsInProcess() )
  {
   // Если окно рамки становится видимым:
   if( TopFrameWindowIsShowing( Message ) )
    {
     // Узнаем окно рамки.
     HWND Frame_window = QueryFrameWindow( Message->hwnd );

     // Если такое окно содержит поля для ввода пароля и их значения надо забрать:
     if( Applier.Settings.Script_after_Logon ) if( Applier_WindowIsPresentInLogonDialogList( Frame_window, 0 ) )
      {
       // Посылаем в очередь сообщение WM_MARK. Когда оно будет получено, окно подготовит все свои кнопки и можно будет проверять его заголовок.
       HMQ Message_queue = WinQueryWindowULong( Frame_window, QWL_HMQ );
       WinPostQueueMsg( Message_queue, WM_MARK, (MPARAM) MRK_LOGON_WINDOW, (MPARAM) Frame_window );
      }

     // Если в таком окне надо заполнять поля при его появлении:
     if( Applier.Settings.Remember_dialog_fields ) if( Applier_WindowIsPresentInIncompleteDialogList( Frame_window, 0 ) )
      {
       // Посылаем в очередь сообщение WM_MARK. Когда оно будет получено, окно подготовит все свои кнопки и можно будет проверять его заголовок.
       HMQ Message_queue = WinQueryWindowULong( Frame_window, QWL_HMQ );
       WinPostQueueMsg( Message_queue, WM_MARK, (MPARAM) MRK_COMPLETE_DIALOG, (MPARAM) Frame_window );
      }

     // Если это окно надо закрывать при появлении:
     if( Applier.Settings.Send_Yes ) if( Applier_WindowIsPresentInMessageDialogList( Frame_window, 0 ) )
      {
       // Посылаем в очередь сообщение WM_MARK. Когда оно будет получено, окно подготовит все свои кнопки и можно будет проверять его заголовок.
       HMQ Message_queue = WinQueryWindowULong( Frame_window, QWL_HMQ );
       WinPostQueueMsg( Message_queue, WM_MARK, (MPARAM) MRK_SEND_YES, (MPARAM) Frame_window );
      }
    }

   // Если есть окна для ввода пароля и одно из окон закрывается:
   if( Applier.RTSettings.Logon_in_process ) if( Message->msg == WM_DESTROY )
    {
     // Если окно есть в списке отслеживаемых окон:
     for( INT Count = APPLIER_MONITORING_LOGON_WINDOWS - 1; Count >= 0; Count -- )
      if( Applier.RTDlgMemory.Logon_windows[ Count ].Window == Message->hwnd )
       {
        // Посылаем сообщение в поток. Он выполнит все необходимые проверки.
        WinPostQueueMsg( Enhancer.Modules.Applier->Message_queue, SM_LOGON_ACTION, (MPARAM) Message->hwnd, 0 );
        break;
       }
    }

   // Если есть окна для ввода пароля и одно из окон становится выбранным:
   if( Applier.RTSettings.Logon_in_process ) if( TopFrameWindowIsActivating( Message ) )
    {
     // Посылаем в поток сообщение о том, что надо проверить существование окон ввода пароля.
     WinPostQueueMsg( Enhancer.Modules.Applier->Message_queue, SM_LOGON_CHECK, 0, 0 );
    }
  }

 // Возврат.
 return;
}
