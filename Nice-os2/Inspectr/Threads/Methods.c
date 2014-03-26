
// ��� �����뢠�� ����ன�� � �����蠥� ࠡ��� �ਫ������ ���

VOID Threads_WriteSettingsAndCloseMainWindow( VOID )
{
 // �᫨ ���� ������� ����ன��:
 if( Inspector.Write_settings )
  {
   // ���뢠�� 䠩� ����஥�.
   CHAR Settings_file_name[ SIZE_OF_PATH ] = "";
   {
    strcpy( Settings_file_name, Inspector.Current_directory );
    CutNameInPath( Settings_file_name ); strcat( Settings_file_name, "\\Nice-os2.ini" );
   }
   HINI Ini_file = OpenIniProfile( Inspector.Application, Settings_file_name );

   if( Ini_file != NULLHANDLE )
    {
     // �����뢠�� ������� �ਫ������.
     INT Count = 0;

     for( Count = 0; Count < Repository.Length; Count ++ )
      {
       if( Repository.Items[ Count ].Object_INI_setting_name[ 0 ] != 0 ) if( Repository.Items[ Count ].Object[ 0 ] != 0 )
        PrfWriteProfileData( Ini_file, "Applications", Repository.Items[ Count ].Object_INI_setting_name, Repository.Items[ Count ].Object, strlen( Repository.Items[ Count ].Object ) + 1 );

       if( Repository.Items[ Count ].Path_INI_setting_name[ 0 ] != 0 ) if( Repository.Items[ Count ].Path[ 0 ] != 0 )
        PrfWriteProfileData( Ini_file, "Applications", Repository.Items[ Count ].Path_INI_setting_name, Repository.Items[ Count ].Path, strlen( Repository.Items[ Count ].Path ) + 1 );
      }

     // ����뢠�� 䠩� ����஥�.
     PrfCloseProfile( Ini_file );
    }

   {
    // ������ ���� ࠡ�祣� �⮫�.
    HWND Desktop = WinQueryDesktopWindow( Inspector.Application, NULLHANDLE );

    // ��ॡ�ࠥ� ���� ࠡ�祣� �⮫�.
    HENUM Enumeration = WinBeginEnumWindows( Desktop ); HWND Window = NULLHANDLE;
    while( ( Window = WinGetNextWindow( Enumeration ) ) != NULLHANDLE )
     {
      // �᫨ �� ���� ����⥫� - ᮮ�頥� ���, �⮡� �� ��祫 ᯨ᮪ �ਫ������.
      if( IsFrameWindow( Window ) && WindowIsCreatedBy( APP_NICE, Window ) )
       {
        CHAR Window_name[ SIZE_OF_NAME ] = ""; 
        WinQueryClassName( WinWindowFromID( Window, FID_CLIENT ), SIZE_OF_NAME, Window_name );

        if( strcmp( Window_name, "NiceOS2WndClass!E" ) == EQUALLY ) 
         WinPostMsg( WinWindowFromID( Window, FID_CLIENT ), SM_RECEIVE_REPOSITORY, (MPARAM) 0, (MPARAM) 0 );
       }
     }
    WinEndEnumWindows( Enumeration );
   }
  }

 // ���뫠�� � ���� �ਫ������ ������� �������.
 WinPostMsg( Inspector.Frame_window, WM_SYSCOMMAND, MPFROMLONG( SC_CLOSE ), 0 );

 // ������.
 return;
}
