
// ��� �������� ��� � ���� � ᯨ᮪ ᢮��� ���

// Frame_window - ���� ࠬ��.
VOID WinPrpListAndRepository_RememberExeNameAndPath( HWND Frame_window )
{
 // ������ ���� � �ਫ������, ᮧ���襬� ����.
 PROCESSINFO Process_info = {0}; QueryProcessInfo( Frame_window, &Process_info, 0 );

 PCHAR Name = Process_info.Exe_name;
 PCHAR Path = Process_info.Exe_path;

 // �᫨ ��� �� 㤠���� ��।����� - ������.
 if( Path[ 0 ] == 0 ) return;

 // �᫨ �� �ᯮ���⥫� ������ ��� ���� �� ��� �ᯮ����⥫��� �ணࠬ� - ������.
 if( IsCommandExecutorWindow( Process_info.Exe_name ) ) return;

 // ��⠭�������� ᢮��⢠.
 SetProperty( Frame_window, PRP_EXENAME, Name );
 SetProperty( Frame_window, PRP_EXEPATH, Path );

 // �᫨ ᯨ᮪ �ਫ������ �� ���⥭:
 if( Krnl_Repository.RTSettings.Repository_is_ready )
  {
   // �஢��塞, ���� �� �� �ਫ������ � ᯨ᪥ �������� �ਫ������.
   INT Position = FindExeNameInRepository( Name );

   // �᫨ ��� ����:
   if( Position != -1 )
    {
     // �᫨ ���� � �ਫ������ ��������� - ���������� ���� ����.
     if( Repository.Items[ Position ].Path_INI_setting_name[ 0 ] != 0 )
      if( strcmp( Repository.Items[ Position ].Path, Path ) != EQUALLY )
       strcpy( Repository.Items[ Position ].Path, Path );
    }
  }

 // ������.
 return;
}
