
// ─── Записывает настройки и завершает работу приложения ───

VOID Threads_WriteSettingsAndCloseMainWindow( VOID )
{
 // Если надо записать настройки:
 if( Inspector.Write_settings )
  {
   // Открываем файл настроек.
   CHAR Settings_file_name[ SIZE_OF_PATH ] = "";
   {
    strcpy( Settings_file_name, Inspector.Current_directory );
    CutNameInPath( Settings_file_name ); strcat( Settings_file_name, "\\Nice-os2.ini" );
   }
   HINI Ini_file = OpenIniProfile( Inspector.Application, Settings_file_name );

   if( Ini_file != NULLHANDLE )
    {
     // Записываем известные приложения.
     INT Count = 0;

     for( Count = 0; Count < Repository.Length; Count ++ )
      {
       if( Repository.Items[ Count ].Known_WPS_object[ 0 ] != 0 )
        if( Repository.Items[ Count ].Object_INI_setting_name[ 0 ] != 0 ) 
         if( !strc( Repository.Items[ Count ].Known_WPS_object, Repository.Items[ Count ].WPS_name_A ) )
          if( !strc( Repository.Items[ Count ].Known_WPS_object, Repository.Items[ Count ].WPS_name_B ) )
           if( !strc( Repository.Items[ Count ].Known_WPS_object, Repository.Items[ Count ].WPS_name_C ) )
            if( !strc( Repository.Items[ Count ].Known_WPS_object, Repository.Items[ Count ].WPS_name_D ) )
             PrfWriteProfileData( Ini_file, "Applications", Repository.Items[ Count ].Object_INI_setting_name, Repository.Items[ Count ].Known_WPS_object, strlen( Repository.Items[ Count ].Known_WPS_object ) + 1 );

       if( Repository.Items[ Count ].Path_to_Exe_file[ 0 ] != 0 )
        if( Repository.Items[ Count ].Path_INI_setting_name[ 0 ] != 0 ) 
         PrfWriteProfileData( Ini_file, "Applications", Repository.Items[ Count ].Path_INI_setting_name, Repository.Items[ Count ].Path_to_Exe_file, strlen( Repository.Items[ Count ].Path_to_Exe_file ) + 1 );
      }

     // Закрываем файл настроек.
     PrfCloseProfile( Ini_file );
    }

   {
    // Узнаем окно рабочего стола.
    HWND Desktop = WinQueryDesktopWindow( Inspector.Application, NULLHANDLE );

    {
     // Перебираем окна в окне рабочего стола.
     HENUM Enumeration = WinBeginEnumWindows( Desktop ); HWND Window = NULLHANDLE;
     while( ( Window = WinGetNextWindow( Enumeration ) ) != NULLHANDLE )
      {
       // Если это окно расширителя - сообщаем ему, чтобы он прочел список приложений.
       if( IsFrameWindow( Window ) && WindowIsCreatedBy( APP_NICE, Window ) )
        {
         CHAR Window_name[ SIZE_OF_NAME ] = ""; 
         WinQueryClassName( WinWindowFromID( Window, FID_CLIENT ), SIZE_OF_NAME, Window_name );

         if( strc( Window_name, "NiceOS2WndClass!E" ) ) 
          WinPostMsg( WinWindowFromID( Window, FID_CLIENT ), SM_RECEIVE_REPOSITORY, (MPARAM) 0, (MPARAM) 0 );
        }
      }
     WinEndEnumWindows( Enumeration );
    }
   }
  }

 // Посылаем в окно приложения команду закрытия.
 WinPostMsg( Inspector.Frame_window, WM_SYSCOMMAND, MPFROMLONG( SC_CLOSE ), 0 );

 // Возврат.
 return;
}
