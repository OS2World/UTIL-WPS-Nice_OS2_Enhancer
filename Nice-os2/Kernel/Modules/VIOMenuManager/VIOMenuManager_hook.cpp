
// ─── Слежение за сообщениями ───

// Все переменные - внешние.
VOID VIOMenuManagerInputHook( HAB Application, PQMSG Message, PBYTE Discarding )
{
 // Изменяем меню SSH при нажатии кнопки мыши в окне картинки.
 if( VIOMenuManager.Settings.SSH_Commands )
  {
   // Если окно получает сообщение о нажатии кнопки мыши:
   if( Message->msg == WM_BUTTON1DOWN || Message->msg == WM_BUTTON2DOWN || Message->msg == WM_BUTTON3DOWN )
    {
     // Если мышь нажата в окне картинки в окне VIO:
     if( IsMenuWindow( Message->hwnd ) )
      {
       HWND Frame_window = NULLHANDLE;
       HWND Parent_window = WinQueryWindow( Message->hwnd, QW_PARENT );
       if( IsFrameWindow( Parent_window ) ) Frame_window = Parent_window;

       if( Frame_window )
        {
         if( IsVIOWindow( Frame_window ) &&
             WinWindowFromID( Frame_window, FID_SYSMENU ) == Message->hwnd )
          {
           // Если это окно SSH - надо считать команды из файлов настроек,
           // а также считать измененные пользователем файлы, если они есть.
           if( WindowIsCreatedBy( APP_SSH, Frame_window ) )
            {
             // Посылаем сообщение в поток.
             // Когда оно будет обработано, в очередь окна придет сообщение WM_MARK.
             INT Markers_quantity = 1;
             WinPostQueueMsg( Enhancer.Modules.VIOMenuManager->Message_queue, SM_CHECK_ALL_COMMANDS, (MPARAM) Frame_window, (MPARAM) Markers_quantity );
            }
          }
        }
      }
    }

   // Добавляем в меню строки после того, как они были считаны потоком.
   // Это действие можно выполнять только в обработчике сообщений окна VIO.
   if( Message->msg == WM_MARK )
    {
     HWND Frame_window = (HWND) Message->mp2;
     if( Message->mp1 == (MPARAM) MRK_ADD_VIO_MENU_ITEMS ) VIOMenuManager_AddItems( Frame_window );
     if( Message->mp1 == (MPARAM) MRK_SHOW_VIO_MENU_ITEMS ) VIOMenuManager_ShowItems( Frame_window );
    }

   // Отправляем выбранную команду в окно.
   if( Message->msg == WM_SYSCOMMAND )
    {
     // Узнаем значение ID выбранной строки.
     ULONG Item_ID = (ULONG) Message->mp1;

     // Если это одна из команд:
     if( VIOMenuManager_IsSSHCommandMenuItem( Item_ID ) )
      {
       // Узнаем окно рамки.
       HWND Frame_window = QueryFrameWindow( Message->hwnd );

       // Если это текстовое окно:
       if( IsVIOWindow( Frame_window ) )
        {
         // Если это окно SSH:
         if( WindowIsCreatedBy( APP_SSH, Frame_window ) )
          {
           // Если известны команды для этого окна:
           INT File_number = VIOMenuManager_GetCommandSubset( Frame_window );

           if( File_number != -1 )
            {
             // Получаем выбранную строку.
             CHAR String[ SIZE_OF_ITEM_TEXT ] = ""; ULONG Length = SIZE_OF_ITEM_TEXT;
             VIOMenuManager_QueryCommandItemText( Frame_window, Item_ID, String, Length );

             // Находим ее в списке команд.
             INT Position = VIOMenuManager_FindCommandInList( File_number, String );

             // Если она была найдена:
             if( Position != -1 )
              {
               // Посылаем сообщение в поток.
               WinPostQueueMsg( Enhancer.Modules.VIOMenuManager->Message_queue, SM_POST_VIO_MENU_ITEM, (MPARAM) Frame_window, (MPARAM) Position );
              }
            }

           // Сообщение должно быть сброшено.
           *Discarding = 1;
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
VOID VIOMenuManagerKbdInputHook( HAB Application, PQMSG Message, PBYTE Discarding )
{
 // Изменяем меню SSH при нажатии "Shift + Esc" и показываем команды в меню при нажатии "Alt + ~".
 if( VIOMenuManager.Settings.SSH_Commands )
  {
   // Если окно получает сообщение о нажатии на клавишу:
   if( Message->msg == WM_CHAR )
    {
     // Смотрим, какая клавиша нажата.
     BYTE Scan_code = CHAR4FROMMP( Message->mp1 );
     SHORT State = SHORT1FROMMP( Message->mp1 );

     // Если это то, что нам нужно:
     ULONG Action = 0; ULONG Add_items = 1; ULONG Show_items = 2;
     if( Scan_code == SC_ESC ) if( State & KC_SHIFT ) Action = Add_items;
     if( Scan_code == SC_BACKQUOTE ) if( State & KC_ALT ) if( VIOMenuManager.Settings.Use_AltTilde ) Action = Show_items;

     if( Action )
      {
       // Если это первое нажатие на клавишу:
       if( !( State & KC_KEYUP ) ) if( !( State & KC_PREVDOWN ) )
        {
         // Узнаем окно рамки.
         HWND Frame_window = QueryFrameWindow( Message->hwnd );

         // Если это текстовое окно:
         if( Frame_window ) if( IsVIOWindow( Frame_window ) )
          {
           // Если это окно SSH - надо считать команды из файлов настроек,
           // а также считать измененные пользователем файлы, если они есть.
           if( WindowIsCreatedBy( APP_SSH, Frame_window ) )
            {
             // Посылаем сообщение в поток.
             // Когда оно будет обработано, в очередь окна придет сообщение WM_MARK.
             INT Markers_quantity = 1; if( Action == Show_items ) Markers_quantity = 2;
             WinPostQueueMsg( Enhancer.Modules.VIOMenuManager->Message_queue, SM_CHECK_ALL_COMMANDS, (MPARAM) Frame_window, (MPARAM) Markers_quantity );
            }
          }
        }

       // Сообщение от клавиши вызова списка действий должно быть сброшено.
       if( Action == Show_items ) *Discarding = 1;
      }
    }
  }

 // Возврат.
 return;
}

