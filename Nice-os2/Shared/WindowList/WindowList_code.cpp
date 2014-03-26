
// ─── Исправляет заголовок окна ───

// Window_title - заголовок, Required_length - требуемая длина.
VOID WindowList_CorrectWindowTitle( HWND Frame_window, PCHAR Window_title, INT Required_length )
{
 // Узнаем длину строки.
 INT String_length = strlen( Window_title );

 // Удаляем в заголовке буквы разрыва строки и слова "Applet Viewer".
 {
  INT Step;

  for( Step = 0; Step < 4; Step ++ )
   {
    // Задаем слово для удаления.
    CHAR Word_for_removing[ 25 ] = ""; INT Length = 1;
    if( Step == 0 ) { Word_for_removing[ 0 ] = 0x0D; Word_for_removing[ 1 ] = 0;   }
    if( Step == 1 ) { Word_for_removing[ 0 ] = 0x0A; Word_for_removing[ 1 ] = 0;   }
    if( Step == 2 ) { strcpy( Word_for_removing, "Applet Viewer: " ); Length = 15; }
    if( Step == 3 ) { strcpy( Word_for_removing, ".class" );          Length = 6;  }

    // Просматриваем строку.
    {
     INT Count = 0;

     while( Window_title[ Count ] != 0 )
      {
       // Проверяем, есть ли совпадение.
       BYTE Words_is_equally = 1; INT Position = 0;
       while( Word_for_removing[ Position ] != 0 )
        {
         if( Window_title[ Count + Position ] != Word_for_removing[ Position ] )
          { Words_is_equally = 0; break; }

         Position ++;
        }

       // Если оно есть - удаляем слово.
       if( Words_is_equally )
        {
         // Вместо разрыва строки надо поставить пробел.
         if( Window_title[ Count ] == 0x0A && Window_title[ Count - 1 ] != ' ' )
          {
           Window_title[ Count ] = ' ';
          }
         // Удаляем слово.
         else
          {
           strcpy( &Window_title[ Count ], &Window_title[ Count + Length ] );
          }
        }

       // Увеличиваем счетчик.
       Count ++;
      }
    }
   }
 }

 // Если заголовок слишком длинный - добавляем к нему многоточие.
 if( String_length >= Required_length - 1 )
  {
   // Строка должна заканчиваться буквой.
   INT Points_length = 3; INT Position = Required_length - 1 - Points_length;

   INT Count = 0;

   while( Count < 100000 )
    {
     CHAR Letter = Window_title[ Position - 1 ];
     if( Letter < 48 || ( Letter > 57 && Letter < 61 ) ) Position --;
     else break;
    }

   // Добавляем многоточие.
   strncpy( &Window_title[ Position ], "...", Points_length );
   Window_title[ Position + Points_length ] = 0;
  }

 // Если заголовок содержит имя исполняемого файла - приводим его к виду "Имя.exe"
 if( String_length > 4 )
  if( Window_title[ String_length - 4 ] == '.' )
   if( !strfind( " ", Window_title ) )
    if( ( Window_title[ String_length - 3 ] == 'E' &&
          Window_title[ String_length - 2 ] == 'X' &&
          Window_title[ String_length - 1 ] == 'E' ) ||
        ( Window_title[ String_length - 3 ] == 'e' &&
          Window_title[ String_length - 2 ] == 'x' &&
          Window_title[ String_length - 1 ] == 'e' ) ||
        ( Window_title[ String_length - 3 ] == 'C' &&
          Window_title[ String_length - 2 ] == 'O' &&
          Window_title[ String_length - 1 ] == 'M' ) ||
        ( Window_title[ String_length - 3 ] == 'c' &&
          Window_title[ String_length - 2 ] == 'o' &&
          Window_title[ String_length - 1 ] == 'm' ) )
     {
      MixedCase( Window_title );
     }

 // Окну Larsen Commander лучше задать простой заголовок вместо "C:\..."
 if( Window_title[ 1 ] == ':' )
  if( WindowIsCreatedBy( APP_LCMD, Frame_window ) )
   {
    CHAR New_title[ SIZE_OF_TITLE ] = "";
    strcpy( New_title, "Larsen Commander - " );
    strcat( New_title, Window_title );

    strcpy( Window_title, New_title );
   }

 // В заголовке обозревателя Mozilla не надо показывать дату его сборки.
 PCHAR Brace = strfind( " {", Window_title );
 if( Brace )
  if( WindowIsCreatedBy( APP_MOZILLA, Frame_window ) )
   *Brace = 0;

 // Возврат.
 return;
}

// ─── Узнает заголовок окна ───

// Все переменные - внешние.
VOID WindowList_QueryWindowTitle( HWND Frame_window, HWND TitleBar_window, PCHAR Window_title, BYTE Update_frame_if_required = 0 )
{
 // Если это не список окон - узнаем, есть ли окно в списке.
 HSWITCH Switch_handle = NULLHANDLE;
 if( !IsWinListWindow( Frame_window ) ) Switch_handle = WinQuerySwitchHandle( Frame_window, NULLHANDLE );

 // Если окно заголовка не задано - узнаем его.
 if( TitleBar_window == NULLHANDLE ) TitleBar_window = WinWindowFromID( Frame_window, FID_TITLEBAR );

 // Узнаем заголовок окна.
 Window_title[ 0 ] = NULL;

 if( Switch_handle != NULLHANDLE ) if( WinWindowFromID( Frame_window, FID_SYSMENU ) != NULLHANDLE )
  {
   SWCNTRL Task = {0}; WinQuerySwitchEntry( Switch_handle, &Task );

   strncpy( Window_title, Task.szSwtitle, SIZE_OF_TITLE );
   Window_title[ SIZE_OF_TITLE - 1 ] = NULL;

   if( strfind( "% ", Window_title ) ) Window_title[ 0 ] = NULL;
   if( Window_title[ strlen( Window_title ) - 1 ] == '%' ) Window_title[ 0 ] = NULL;
  }

 if( Window_title[ 0 ] == NULL )
  {
   WinQueryWindowText( TitleBar_window, SIZE_OF_TITLE, Window_title );
  }

 #ifndef INCLUDED_BY_SHELL

 // Если это плоское окно сообщения - узнаем текст в его первой строке.
 if( Window_title[ 0 ] == NULL )
  if( TitleBar_window == NULLHANDLE )
   if( Switch_handle == NULLHANDLE )
    if( FrameType( Frame_window ) == FT_FLAT )
     {
      HWND Button = WinWindowFromID( Frame_window, MSGBOX_OK_BUTTON );
      if( Button != NULLHANDLE ) if( IsButtonWindow( Button ) )
       {
        HWND Message = WinWindowFromID( Frame_window, MSGBOX_MESSAGE_TEXT );
        if( Message != NULLHANDLE )
         {
          HWND Title_window = WinWindowFromID( Frame_window, MSGBOX_TITLE_TEXT );
          if( Title_window != NULLHANDLE )
           WinQueryWindowText( Title_window, SIZE_OF_TITLE, Window_title );
         }
       }
     }

 // Некоторые окна не имеют заголовка.
 if( Window_title[ 0 ] == NULL )
  {
   BYTE Window_code_page = QueryCodePage( Frame_window ); BYTE Change_real_title = 0;

   // Если это справочник или системное сообщение - устанавливаем свой заголовок.
   if( WindowIsCreatedBy( APP_VIEWDOC, Frame_window ) )
    {
     if( Window_code_page == RUSSIAN ) strcpy( Window_title, "Справочник" );
     else strcpy( Window_title, "Help" );
    }

   if( IsSysMsgWindow( Frame_window ) )
    {
     if( Window_code_page == RUSSIAN ) strcpy( Window_title, "Ошибка" );
     else strcpy( Window_title, "Error" );

     Change_real_title = 1;
    }

   // Устанавливаем настоящий заголовок, если это требуется.
   if( Change_real_title == 1 ) WinSetWindowText( TitleBar_window, Window_title );

   // Если заголовка нет:
   if( Window_title[ 0 ] == NULL )
    {
     // Устанавливаем значение по умолчанию.
     if( Window_code_page == RUSSIAN ) strcpy( Window_title, "Окно" );
     else strcpy( Window_title, "Window" );

     // Изменяем заголовок окна, если это требуется.
     if( Update_frame_if_required ) WinSetWindowText( TitleBar_window, Window_title );
    }
  }

 #endif

 // Исправляем заголовок окна.
 WindowList_CorrectWindowTitle( Frame_window, Window_title, SIZE_OF_TITLE );

 // Возврат.
 return;
}

#ifndef INCLUDED_BY_SHELL

// ─── Возвращает заголовок для окна рабочего стола ───

// Window_title - заголовок окна.
VOID WindowList_GetDefaultShellTitle( PCHAR Window_title )
{
 // Возвращаем заголовок.
 BYTE Desktop_code_page = QueryCodePage( QueryDesktopWindow() );

 if( Desktop_code_page == RUSSIAN ) strcpy( Window_title, "Рабочий стол" );
 else strcpy( Window_title, "Desktop" );

 // *********************************************************************** //
 // "Desktop",                                                              //
 // "Рабочий стол",                                                         //
 // "\x83\x66\x83\x58\x83\x4E\x83\x67\x83\x62\x83\x76",                     //
 // "Escritorio",                                                           //
 // "Werkplek",                                                             //
 // "\x41\x72\x62\x65\x69\x74\x73\x6f\x62\x65\x72\x66\x6c\x84\x63\x68\x65", //
 // "Area di lavoro",                                                       //
 // "Scrivania",                                                            //
 // *********************************************************************** //

 // Возврат.
 return;
}

#endif

// ─── Получает список окон ───

// SWBlock и Corrected_SWBlock - пустые указатели.
VOID WindowList_QuerySWBlocks( PSWBLOCK* SWBlock, PSWBLOCK* Corrected_SWBlock )
{
 INT Number_of_items; INT SWBlock_length;

 // Узнаем, сколько памяти потребуется для списка.
 HAB Application = ActiveApplication();

 Number_of_items = WinQuerySwitchList( Application, NULL, 0 );
 SWBlock_length = ( Number_of_items * sizeof( SWENTRY ) ) + sizeof( HSWITCH );

 // Выделяем память.
 DosAllocMem( (PPVOID) SWBlock, SWBlock_length, PAG_ALLOCATE );
 DosAllocMem( (PPVOID) Corrected_SWBlock, SWBlock_length, PAG_ALLOCATE );

 // Узнаем список окон.
 WinQuerySwitchList( Application, *SWBlock, SWBlock_length );
 memcpy( *Corrected_SWBlock, *SWBlock, SWBlock_length );

 // Исправляем его.
 {
  INT Count;

  for( Count = 0; Count < ( *Corrected_SWBlock )->cswentry; Count ++ )
   {
    PSWCNTRL Task = &( ( *Corrected_SWBlock )->aswentry[ Count ].swctl );
    WindowList_CorrectWindowTitle( Task->hwnd, Task->szSwtitle, SIZE_OF_NAME );
   }
 }

 // Возврат.
 return;
}

// ─── Освобождает память ───

// SWBlock и Corrected_SWBlock - указатели на области памяти.
VOID WindowList_FreeSWBlockMemory( PSWBLOCK SWBlock, PSWBLOCK Corrected_SWBlock )
{
 // Освобождаем память.
 if( SWBlock ) DosFreeMem( SWBlock );
 if( Corrected_SWBlock ) DosFreeMem( Corrected_SWBlock );

 // Возврат.
 return;
}

// ─── Узнает список окон ───

// SWBlock - пустой указатель.
VOID WindowList_QuerySwitchList( PSWBLOCK* SWBlock )
{
 // Получаем список окон.
 PSWBLOCK Temporary_SWBlock = NULL;
 WindowList_QuerySWBlocks( &Temporary_SWBlock, SWBlock );
 WindowList_FreeSWBlockMemory( Temporary_SWBlock, NULL );

 // Возврат.
 return;
}

// ─── Освобождает память ───

// SWBlock - указатель на область памяти.
VOID WindowList_FreeSwitchListMemory( PSWBLOCK SWBlock )
{
 // Освобождаем память.
 WindowList_FreeSWBlockMemory( NULL, SWBlock );

 // Возврат.
 return;
}

// ─── Показывает или скрывает строку в списке окон ───

// Switch_handle, Task - строка, Show_item - что надо сделать.
VOID WindowList_ShowItemInSwitchList( HSWITCH Switch_handle, SWCNTRL Task, BYTE Show_item )
{
 // Скрываем или показываем строку.
 if( Show_item )
  {
   Task.uchVisibility = SWL_VISIBLE;
   Task.fbJump = SWL_JUMPABLE;
  }
 else
  {
   Task.uchVisibility = SWL_INVISIBLE;
   Task.fbJump = SWL_NOTJUMPABLE;
  }

 WinChangeSwitchEntry( Switch_handle, &Task );

 // Возврат.
 return;
}

// ─── Показывает или скрывает строку в списке окон ───

// Item_name - строка, Show_item - что надо сделать.
VOID WindowList_ShowItemInSwitchList( PCHAR Item_name, BYTE Show_item )
{
 // Узнаем список окон.
 PSWBLOCK SWBlock = NULL; PSWBLOCK Corrected_SWBlock = NULL;
 WindowList_QuerySWBlocks( &SWBlock, &Corrected_SWBlock );

 // Показываем или скрываем строку.
 {
  INT Count;

  for( Count = 0; Count < Corrected_SWBlock->cswentry; Count ++ )
   {
    HSWITCH Switch_handle = SWBlock->aswentry[ Count ].hswitch;
    SWCNTRL Task = Corrected_SWBlock->aswentry[ Count ].swctl;
    PCHAR Title = Corrected_SWBlock->aswentry[ Count ].swctl.szSwtitle;

    if( strcmp( Title, Item_name ) == EQUALLY ) WindowList_ShowItemInSwitchList( Switch_handle, Task, Show_item );
   }
 }

 // Освобождаем память.
 WindowList_FreeSWBlockMemory( SWBlock, Corrected_SWBlock ); SWBlock = Corrected_SWBlock = NULL;

 // Возврат.
 return;
}

