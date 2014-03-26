
// ��� ��뢠�� �ࠢ�筨� ���

VOID HelpPages_Help( INT Topic, ULONG Code_page )
{
 // ������ �������� ࠧ����.
 CHAR Topic_name[ SIZE_OF_NAME ] = "";

 switch( Topic )
  {
   case SET_SCROLLING:
    if( Code_page == RUSSIAN ) strcpy( Topic_name, "��।�������" );
    else strcpy( Topic_name, "Advanced" );
   break;

   case SET_DRAWING:
    if( Code_page == RUSSIAN ) strcpy( Topic_name, "���譨�" );
    else strcpy( Topic_name, "Window" );
   break;

   case SET_ROOMS:
    if( Code_page == RUSSIAN ) strcpy( Topic_name, "�������" );
    else strcpy( Topic_name, "Rooms" );
   break;

   case SET_KEYBOARD:
    if( Code_page == RUSSIAN ) strcpy( Topic_name, "���������" );
    else strcpy( Topic_name, "Keyboard" );
   break;

   case SET_MOUSE:
    if( Code_page == RUSSIAN ) strcpy( Topic_name, "����⢨�" );
    else strcpy( Topic_name, "Mouse" );
   break;

   case SET_PLACEMENT:
    if( Code_page == RUSSIAN ) strcpy( Topic_name, "��ࠢ�������" );
    else strcpy( Topic_name, "Change" );
   break;

   case SET_DIALOG_BOXES:
    if( Code_page == RUSSIAN ) strcpy( Topic_name, "����" );
    else strcpy( Topic_name, "Dialog" );
   break;

   case SET_FILE_WINDOWS:
    if( Code_page == RUSSIAN ) strcpy( Topic_name, "�����" );
    else strcpy( Topic_name, "Drive" );
   break;

   case SET_PRIORITY:
    if( Code_page == RUSSIAN ) strcpy( Topic_name, "�ਮ����" );
    else strcpy( Topic_name, "Priority" );
   break;

   case SET_WINLIST:
    if( Code_page == RUSSIAN ) strcpy( Topic_name, "���᮪" );
    else strcpy( Topic_name, "Window List" );
   break;

   case SET_VIO_WINDOWS:
    if( Code_page == RUSSIAN ) strcpy( Topic_name, "����⮢�" );
    else strcpy( Topic_name, "VIO" );
   break;

   case SET_SYS_PATCHES:
    if( Code_page == RUSSIAN ) strcpy( Topic_name, "�����⪨" );
    else strcpy( Topic_name, "System" );
   break;
  }

 // ��뢠�� �ࠢ�筨�.
 if( Topic_name[ 0 ] != 0 )
  {
   CHAR Viewer[ SIZE_OF_PATH ] = "View.exe";

   CHAR Chapter[ SIZE_OF_PATH ] = ""; GetCurrentPath( Chapter );
   strcat( Chapter, "\\Nice-os2.inf " ); strcat( Chapter, Topic_name );

   Execute( Viewer, Chapter );
  }

 // ������.
 return;
}

// ��� ����뢠�� �ࠢ�筨� ���

VOID HelpPages_CloseExistingHelpPage( VOID )
{
 // ��ॡ�ࠥ� ���� � ���� ࠡ�祣� �⮫�.
 HWND Window = NULLHANDLE;

 HENUM Enumeration = WinBeginEnumWindows( QueryDesktopWindow() );
 while( ( Window = WinGetNextWindow( Enumeration ) ) != NULLHANDLE )
  {
   // �᫨ �� �ࠢ�筨�:
   if( IsFrameWindow( Window ) ) if( WindowIsUsedTo( DO_BROWSE_IPF_HELP, Window ) )
    {
     // ������ ��������� ����.
     CHAR Window_title[ SIZE_OF_TITLE ] = "";
     WinQueryWindowText( WinWindowFromID( Window, FID_TITLEBAR ), SIZE_OF_TITLE, Window_title );

     // �᫨ �� �ࠢ�筨� ����⥫� - ����뢠�� ����.
     if( strifind( "Nice", Window_title ) ) WinPostMsg( Window, WM_SYSCOMMAND, (MPARAM) SC_CLOSE, MPFROM2SHORT( CMDSRC_MENU, 0 ) );
    }
  }

 // ������.
 return;
}

