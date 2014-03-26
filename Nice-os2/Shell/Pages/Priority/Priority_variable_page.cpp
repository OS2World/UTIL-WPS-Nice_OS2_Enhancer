
// ��� ��ࠡ��稪 ᮮ�饭�� ��� ���� ���

// ��⮪ �ਫ������ ��뢠�� WindowProc ��直� ࠧ, ����� ��� ���� ���� ᮮ�饭��.
// Window - ����, Message - ᮮ�饭��, *_parameter - �����, ����� ��।����� ����� � ᮮ�饭���.
MRESULT EXPENTRY Priority_Variable_WndProc( HWND Window, ULONG Message, MPARAM First_parameter, MPARAM Second_parameter )
{
 // �����⥫� �� ��࠭���.
 PPAGE Page = Enhancer.Pages.Priority_variable;

 // �஢��塞 ᮮ�饭��.
 switch( Message )
  {
   // �⮡ࠦ��� ����ன��.
   case SM_SHOW_SETTINGS:
    {
     BYTE Value = 0; if( PriorityManager.Settings.Dynamic_priority ) Value = 1;
     WinSendDlgItemMsg( Window, Priority_Variable.Settings.Calculate_ID, BM_SETCHECK, MPFROMLONG( Value ), 0 );
     WinEnableControl( Window, Priority_Variable.Settings.VIO_ID, Value );
     WinEnableControl( Window, Priority_Variable.Settings.lSwitcher_ID, Value );

     Value = 0; if( PriorityManager.Settings.Dynamic_priority_for_VIO ) Value = 1;
     WinSendDlgItemMsg( Window, Priority_Variable.Settings.VIO_ID, BM_SETCHECK, MPFROMLONG( Value ), 0 );

     Value = 0; if( PriorityManager.Settings.Dynamic_priority_for_lSwitcher ) Value = 1;
     WinSendDlgItemMsg( Window, Priority_Variable.Settings.lSwitcher_ID, BM_SETCHECK, MPFROMLONG( Value ), 0 );
    }
   return 0;

   // ������ �� ���ﬨ �����.
   case WM_CONTROL:
    {
     ULONG WM_Control_Window_ID = SHORT1FROMMP( First_parameter );
     ULONG WM_Control_Action_ID = SHORT2FROMMP( First_parameter );

     if( WM_Control_Window_ID == Priority_Variable.Settings.Calculate_ID )
      {
       switch( WM_Control_Action_ID )
        {
         case BN_CLICKED:
         case BN_DBLCLICKED:
          {
           ULONG Button_is_checked = (ULONG) WinSendDlgItemMsg( Window, WM_Control_Window_ID, BM_QUERYCHECK, 0, 0 );

           if( Button_is_checked ) PriorityManager.Settings.Dynamic_priority = 0;
           else PriorityManager.Settings.Dynamic_priority = 1;

           WinSendMsg( Window, SM_SHOW_SETTINGS, 0, 0 );
          }
         break;
        }
      }

     if( WM_Control_Window_ID == Priority_Variable.Settings.VIO_ID )
      {
       switch( WM_Control_Action_ID )
        {
         case BN_CLICKED:
         case BN_DBLCLICKED:
          {
           ULONG Button_is_checked = (ULONG) WinSendDlgItemMsg( Window, WM_Control_Window_ID, BM_QUERYCHECK, 0, 0 );

           if( Button_is_checked ) PriorityManager.Settings.Dynamic_priority_for_VIO = 0;
           else PriorityManager.Settings.Dynamic_priority_for_VIO = 1;

           WinSendMsg( Window, SM_SHOW_SETTINGS, 0, 0 );
          }
         break;
        }
      }

     if( WM_Control_Window_ID == Priority_Variable.Settings.lSwitcher_ID )
      {
       switch( WM_Control_Action_ID )
        {
         case BN_CLICKED:
         case BN_DBLCLICKED:
          {
           ULONG Button_is_checked = (ULONG) WinSendDlgItemMsg( Window, WM_Control_Window_ID, BM_QUERYCHECK, 0, 0 );

           if( Button_is_checked ) PriorityManager.Settings.Dynamic_priority_for_lSwitcher = 0;
           else PriorityManager.Settings.Dynamic_priority_for_lSwitcher = 1;

           WinSendMsg( Window, SM_SHOW_SETTINGS, 0, 0 );
          }
         break;
        }
      }
    }
   return 0;

   // ��ࠡ��뢠�� ������ �� ������.
   case WM_COMMAND:
    {
     ULONG WM_Control_Button_ID = SHORT1FROMMP( First_parameter );

     if( WM_Control_Button_ID == OK_BUTTON_ID )
      {
       CHAR Settings_file_name[ SIZE_OF_PATH ] = ""; GetSettingsFileName( Settings_file_name );
       HINI Ini_file = OpenIniProfile( Enhancer.Application, Settings_file_name );

       if( Ini_file )
        {
         PrfWriteProfileData( Ini_file, "Settings", "Dynamic priority", &PriorityManager.Settings.Dynamic_priority, sizeof( BYTE ) );
         PrfWriteProfileData( Ini_file, "Settings", "Dynamic priority for VIO", &PriorityManager.Settings.Dynamic_priority_for_VIO, sizeof( BYTE ) );
         PrfWriteProfileData( Ini_file, "Settings", "Dynamic priority for lSwitcher", &PriorityManager.Settings.Dynamic_priority_for_lSwitcher, sizeof( BYTE ) );

         PrfCloseProfile( Ini_file );

         BroadcastRSMessages();
         NiceReadSettings();
        }
      }

     if( WM_Control_Button_ID == PD_BUTTON_ID )
      {
       if( Page->SetDefSettings ) Page->SetDefSettings( Page->Settings_to_show );
       if( Page->SetDefSettings_Ext1 ) Page->SetDefSettings_Ext1( Page->Settings_to_show );
       if( Page->SetDefSettings_Ext2 ) Page->SetDefSettings_Ext2( Page->Settings_to_show );
       if( Page->SetDefSettings_Ext3 ) Page->SetDefSettings_Ext3( Page->Settings_to_show );

       WinPostMsg( Window, WM_COMMAND, (MPARAM) OK_BUTTON_ID, 0 );
      }

     if( WM_Control_Button_ID == HP_BUTTON_ID )
      {
       Help( Page->Settings_to_show, Enhancer.Code_page );
      }
    }
   return 0;
  }

 // ������.
 return WinDefWindowProc( Window, Message, First_parameter, Second_parameter );
}
