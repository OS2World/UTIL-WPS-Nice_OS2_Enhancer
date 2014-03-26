
// ��� ��室�� ���� � ᯨ᪥ �������� ���

// Frame_window - ����, Check_title - ���� �� �஢����� ��������� ����, Dialog - 㪠��⥫� �� ᯨ᮪ ��������.
VOID Applier_FindWindowInMessageDialogList( HWND Frame_window, BYTE Check_title, PPMSGDLGBOX Dialog )
{
 // ������ ��� �ਫ������, ᮧ���襣� ����.
 CHAR Exe_name[ SIZE_OF_NAME ] = ""; GetDetectedExeName( Frame_window, Exe_name );

 // �᫨ ��� 㤠���� ��।�����:
 if( Exe_name[ 0 ] != 0 )
  {
   // ������, ��� �룫廊� ࠬ�� ����.
   LONG Frame_type = FrameType( Frame_window );

   // �᫨ ���� �஢����� ��������� ���� - 㧭��� ���. �᫨ �� �������⥭ - �ᯮ��㥬 ������ ��ப�.
   CHAR Title[ SIZE_OF_TITLE ] = "";

   if( Check_title )
    {
     GetDetectedWindowTitle( Frame_window, Title );
     if( Title[ 0 ] == 0 ) strcpy( Title, "-" );
    }

   // ���⠢�塞 ᯨ᮪ �������� ����⥫� ���������� ����.
   PMSGDLGBOX DlgList[ 8 ] = {
                                &Applier.Settings.Dialogs.Message_dialog_1, &Applier.Settings.Dialogs.Message_dialog_2,
                                &Applier.Settings.Dialogs.Message_dialog_3, &Applier.Settings.Dialogs.Message_dialog_4,
                                &Applier.Settings.Dialogs.Message_dialog_5, &Applier.Settings.Dialogs.Message_dialog_6,
                                &Applier.Settings.Dialogs.Message_dialog_7, &Applier.Settings.Dialogs.Message_dialog_8 };

   // �᫨ ⠪�� ���� 㦥 ���� � ᯨ᪥ - ������.
   for( INT Count = 0; Count < 8; Count ++ )
    {
     // �᫨ ᯨ᮪ ��ᬮ�७ - �����蠥� ��ॡ��.
     if( DlgList[ Count ]->Frame_type == 0 ) break;

     // �᫨ ���� ����� ��㣮� ��� ࠬ�� - �த������ ��ॡ��.
     if( Frame_type != DlgList[ Count ]->Frame_type )
      continue;

     // �᫨ ���� ᮧ���� ��㣨� �ਫ������� - �த������ ��ॡ��.
     if( DlgList[ Count ]->Exe_name[ 0 ] != 0 )
      if( strcmp( Exe_name, DlgList[ Count ]->Exe_name ) != EQUALLY )
       continue;

     // �᫨ ���� �஢����� ��������� ����:
     if( Title[ 0 ] != 0 )
      {
       // �᫨ � ���� ��㣮� ��������� - �த������ ��ॡ��.
       if( DlgList[ Count ]->Window_title[ 0 ] != 0 )
        if( strcmp( Title, DlgList[ Count ]->Window_title ) != EQUALLY )
         continue;
      }

     // ���������� ����.
     *Dialog = DlgList[ Count ]; break;
    }
  }

 // ������.
 return;
}

// ��� �஢����, ���� �� ���� � ᯨ᪥ �������� ���

// Frame_window - ����, Check_title - ���� �� �஢����� ��������� ����.
BYTE Applier_WindowIsPresentInMessageDialogList( HWND Frame_window, BYTE Check_title )
{
 // �஡㥬 ���� ���� � ����� �� ᯨ᪮�.
 PMSGDLGBOX Message_dialog = NULL; Applier_FindWindowInMessageDialogList( Frame_window, Check_title, &Message_dialog );
 if( Message_dialog != NULL ) return 1;

 // ������.
 return 0;
}

// ��� ��室�� ���� � ᯨ᪥ �������� ���

// Frame_window - ����, Check_title - ���� �� �஢����� ��������� ����, Dialog - 㪠��⥫� �� ᯨ᮪ ��������.
VOID Applier_FindWindowInIncompleteDialogList( HWND Frame_window, BYTE Check_title, PPDLGBOX Dialog )
{
 // ������ ��� �ਫ������, ᮧ���襣� ����.
 CHAR Exe_name[ SIZE_OF_NAME ] = ""; GetDetectedExeName( Frame_window, Exe_name );

 // �᫨ ��� 㤠���� ��।�����:
 if( Exe_name[ 0 ] != 0 )
  {
   // ������, ��� �룫廊� ࠬ�� ����.
   LONG Frame_type = FrameType( Frame_window );

   // �᫨ ���� �஢����� ��������� ���� - 㧭��� ���. �᫨ �� �������⥭ - �ᯮ��㥬 ������ ��ப�.
   CHAR Title[ SIZE_OF_TITLE ] = "";

   if( Check_title )
    {
     GetDetectedWindowTitle( Frame_window, Title );
     if( Title[ 0 ] == 0 ) strcpy( Title, "-" );
    }

   // ���⠢�塞 ᯨ᮪ �������� ����⥫� ���������� ����.
   PDLGBOX DlgList[ 8 ] = {
                                &Applier.Settings.Dialogs.Incomplete_dialog_1, &Applier.Settings.Dialogs.Incomplete_dialog_2,
                                &Applier.Settings.Dialogs.Incomplete_dialog_3, &Applier.Settings.Dialogs.Incomplete_dialog_4,
                                &Applier.Settings.Dialogs.Incomplete_dialog_5, &Applier.Settings.Dialogs.Incomplete_dialog_6,
                                &Applier.Settings.Dialogs.Incomplete_dialog_7, &Applier.Settings.Dialogs.Incomplete_dialog_8 };

   // �᫨ ⠪�� ���� 㦥 ���� � ᯨ᪥ - ������.
   for( INT Count = 0; Count < 8; Count ++ )
    {
     // �᫨ ᯨ᮪ ��ᬮ�७ - �����蠥� ��ॡ��.
     if( DlgList[ Count ]->Frame_type == 0 ) break;

     // �᫨ ���� ����� ��㣮� ��� ࠬ�� - �த������ ��ॡ��.
     if( Frame_type != DlgList[ Count ]->Frame_type )
      continue;

     // �᫨ ���� ᮧ���� ��㣨� �ਫ������� - �த������ ��ॡ��.
     if( DlgList[ Count ]->Exe_name[ 0 ] != 0 )
      if( strcmp( Exe_name, DlgList[ Count ]->Exe_name ) != EQUALLY )
       continue;

     // �᫨ ���� �஢����� ��������� ����:
     if( Title[ 0 ] != 0 )
      {
       // �᫨ � ���� ��㣮� ��������� - �த������ ��ॡ��.
       if( DlgList[ Count ]->Window_title[ 0 ] != 0 )
        if( strcmp( Title, DlgList[ Count ]->Window_title ) != EQUALLY )
         continue;
      }

     // ���������� ����.
     *Dialog = DlgList[ Count ]; break;
    }
  }

 // ������.
 return;
}

// ��� �஢����, ���� �� ���� � ᯨ᪥ �������� ���

// Frame_window - ����, Check_title - ���� �� �஢����� ��������� ����.
BYTE Applier_WindowIsPresentInIncompleteDialogList( HWND Frame_window, BYTE Check_title )
{
 // �஡㥬 ���� ���� � ����� �� ᯨ᪮�.
 PDLGBOX Incomplete_dialog = NULL; Applier_FindWindowInIncompleteDialogList( Frame_window, Check_title, &Incomplete_dialog );
 if( Incomplete_dialog != NULL ) return 1;

 // ������.
 return 0;
}

// ��� ��室�� ���� � ᯨ᪥ �������� ���

// Frame_window - ����, Check_title - ���� �� �஢����� ��������� ����, Dialog - 㪠��⥫� �� ᯨ᮪ ��������.
VOID Applier_FindWindowInLogonDialogList( HWND Frame_window, BYTE Check_title, PPLOGONDLGBOX Dialog )
{
 // ������ ��� �ਫ������, ᮧ���襣� ����.
 CHAR Exe_name[ SIZE_OF_NAME ] = ""; GetDetectedExeName( Frame_window, Exe_name );

 // �᫨ ��� 㤠���� ��।�����:
 if( Exe_name[ 0 ] != 0 )
  {
   // ������, ��� �룫廊� ࠬ�� ����.
   LONG Frame_type = FrameType( Frame_window );

   // �᫨ ���� �஢����� ��������� ���� - 㧭��� ���. �᫨ �� �������⥭ - �ᯮ��㥬 ������ ��ப�.
   CHAR Title[ SIZE_OF_TITLE ] = "";

   if( Check_title )
    {
     GetDetectedWindowTitle( Frame_window, Title );
     if( Title[ 0 ] == 0 ) strcpy( Title, "-" );
    }

   // ���⠢�塞 ᯨ᮪ �������� ����⥫� ���������� ����.
   PLOGONDLGBOX DlgList[ 8 ] = {
                                &Applier.Settings.Dialogs.Logon_dialog_1, &Applier.Settings.Dialogs.Logon_dialog_2,
                                &Applier.Settings.Dialogs.Logon_dialog_3, &Applier.Settings.Dialogs.Logon_dialog_4,
                                &Applier.Settings.Dialogs.Logon_dialog_5, &Applier.Settings.Dialogs.Logon_dialog_6,
                                &Applier.Settings.Dialogs.Logon_dialog_7, &Applier.Settings.Dialogs.Logon_dialog_8 };

   // �᫨ ⠪�� ���� 㦥 ���� � ᯨ᪥ - ������.
   for( INT Count = 0; Count < 8; Count ++ )
    {
     // �᫨ ᯨ᮪ ��ᬮ�७ - �����蠥� ��ॡ��.
     if( DlgList[ Count ]->Frame_type == 0 ) break;

     // �᫨ ���� ����� ��㣮� ��� ࠬ�� - �த������ ��ॡ��.
     if( Frame_type != DlgList[ Count ]->Frame_type )
      continue;

     // �᫨ ���� ᮧ���� ��㣨� �ਫ������� - �த������ ��ॡ��.
     if( DlgList[ Count ]->Exe_name[ 0 ] != 0 )
      if( strcmp( Exe_name, DlgList[ Count ]->Exe_name ) != EQUALLY )
       continue;

     // �᫨ ���� �஢����� ��������� ����:
     if( Title[ 0 ] != 0 )
      {
       // �᫨ � ���� ��㣮� ��������� - �த������ ��ॡ��.
       if( DlgList[ Count ]->Window_title[ 0 ] != 0 )
        if( strcmp( Title, DlgList[ Count ]->Window_title ) != EQUALLY )
         continue;
      }

     // ���������� ����.
     *Dialog = DlgList[ Count ]; break;
    }
  }

 // ������.
 return;
}

// ��� �஢����, ���� �� ���� � ᯨ᪥ �������� ���

// Frame_window - ����, Check_title - ���� �� �஢����� ��������� ����.
BYTE Applier_WindowIsPresentInLogonDialogList( HWND Frame_window, BYTE Check_title )
{
 // �஡㥬 ���� ���� � ����� �� ᯨ᪮�.
 PLOGONDLGBOX Logon_dialog = NULL; Applier_FindWindowInLogonDialogList( Frame_window, Check_title, &Logon_dialog );
 if( Logon_dialog != NULL ) return 1;

 // ������.
 return 0;
}

