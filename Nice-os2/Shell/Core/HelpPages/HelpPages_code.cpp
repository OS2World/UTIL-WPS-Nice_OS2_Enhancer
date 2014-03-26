
// ─── Вызывает справочник ───

VOID HelpPages_Help( INT Topic, ULONG Code_page )
{
 // Задаем название раздела.
 CHAR Topic_name[ SIZE_OF_NAME ] = "";

 switch( Topic )
  {
   case SET_SCROLLING:
    if( Code_page == RUSSIAN ) strcpy( Topic_name, "Передвижение" );
    else strcpy( Topic_name, "Advanced" );
   break;

   case SET_DRAWING:
    if( Code_page == RUSSIAN ) strcpy( Topic_name, "Внешний" );
    else strcpy( Topic_name, "Window" );
   break;

   case SET_ROOMS:
    if( Code_page == RUSSIAN ) strcpy( Topic_name, "Комнаты" );
    else strcpy( Topic_name, "Rooms" );
   break;

   case SET_KEYBOARD:
    if( Code_page == RUSSIAN ) strcpy( Topic_name, "Клавиатура" );
    else strcpy( Topic_name, "Keyboard" );
   break;

   case SET_MOUSE:
    if( Code_page == RUSSIAN ) strcpy( Topic_name, "Действия" );
    else strcpy( Topic_name, "Mouse" );
   break;

   case SET_PLACEMENT:
    if( Code_page == RUSSIAN ) strcpy( Topic_name, "Выравнивание" );
    else strcpy( Topic_name, "Change" );
   break;

   case SET_DIALOG_BOXES:
    if( Code_page == RUSSIAN ) strcpy( Topic_name, "Окна" );
    else strcpy( Topic_name, "Dialog" );
   break;

   case SET_FILE_WINDOWS:
    if( Code_page == RUSSIAN ) strcpy( Topic_name, "Работа" );
    else strcpy( Topic_name, "Drive" );
   break;

   case SET_PRIORITY:
    if( Code_page == RUSSIAN ) strcpy( Topic_name, "Приоритеты" );
    else strcpy( Topic_name, "Priority" );
   break;

   case SET_WINLIST:
    if( Code_page == RUSSIAN ) strcpy( Topic_name, "Список" );
    else strcpy( Topic_name, "Window List" );
   break;

   case SET_VIO_WINDOWS:
    if( Code_page == RUSSIAN ) strcpy( Topic_name, "Текстовые" );
    else strcpy( Topic_name, "VIO" );
   break;

   case SET_SYS_PATCHES:
    if( Code_page == RUSSIAN ) strcpy( Topic_name, "Заплатки" );
    else strcpy( Topic_name, "System" );
   break;
  }

 // Вызываем справочник.
 if( Topic_name[ 0 ] != 0 )
  {
   CHAR Viewer[ SIZE_OF_PATH ] = "View.exe";

   CHAR Chapter[ SIZE_OF_PATH ] = ""; GetCurrentPath( Chapter );
   strcat( Chapter, "\\Nice-os2.inf " ); strcat( Chapter, Topic_name );

   Execute( Viewer, Chapter );
  }

 // Возврат.
 return;
}

// ─── Закрывает справочник ───

VOID HelpPages_CloseExistingHelpPage( VOID )
{
 // Перебираем окна в окне рабочего стола.
 HWND Window = NULLHANDLE;

 HENUM Enumeration = WinBeginEnumWindows( QueryDesktopWindow() );
 while( ( Window = WinGetNextWindow( Enumeration ) ) != NULLHANDLE )
  {
   // Если это справочник:
   if( IsFrameWindow( Window ) ) if( WindowIsUsedTo( DO_BROWSE_IPF_HELP, Window ) )
    {
     // Узнаем заголовок окна.
     CHAR Window_title[ SIZE_OF_TITLE ] = "";
     WinQueryWindowText( WinWindowFromID( Window, FID_TITLEBAR ), SIZE_OF_TITLE, Window_title );

     // Если это справочник расширителя - закрываем окно.
     if( strifind( "Nice", Window_title ) ) WinPostMsg( Window, WM_SYSCOMMAND, (MPARAM) SC_CLOSE, MPFROM2SHORT( CMDSRC_MENU, 0 ) );
    }
  }

 // Возврат.
 return;
}

