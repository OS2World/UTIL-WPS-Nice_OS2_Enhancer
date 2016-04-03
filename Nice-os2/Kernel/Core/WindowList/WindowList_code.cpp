
// ��� ������ ���� ����㯭� ��� ������㯭� ��� ��४��祭�� �� Alt+Tab ���

// Frame_window - ���� ࠬ��, Flag - ���祭��.
VOID Krnl_WindowList_SetJumpableFlag( HWND Frame_window, ULONG Flag )
{
 // ������, ���� �� ���� � ᯨ᪥ ����.
 HSWITCH Switch_handle = WinQuerySwitchHandle( Frame_window, NULLHANDLE );

 // �᫨ ��� ����:
 if( Switch_handle != NULLHANDLE )
  {
   // ������ ᢮��⢠ ����.
   SWCNTRL Task = {0}; WinQuerySwitchEntry( Switch_handle, &Task );

   // �᫨ ��� �뫨 ����祭�:
   if( Task.hwnd != NULLHANDLE )
    {
     // �᫨ ���� ������㯭� � ᯨ᪥ ���� - ��祣� ������ �� ����.
     if( Task.uchVisibility != SWL_VISIBLE ) return;

     // ���塞 ᢮��⢠.
     if( Task.fbJump != Flag )
      {
       Task.fbJump = Flag;
       WinChangeSwitchEntry( Switch_handle, &Task );
      }
    }
  }

 // ������.
 return;
}

// ��� ������ �� ���� �ਫ������ ����㯭묨 ��� ������㯭묨 ��� ��४��祭�� ���

// WinList_title - �������� � ᯨ᪥ ����, Flag - ���祭��.
VOID Krnl_WindowList_SetProcessJumpableFlag( PCHAR WinList_title, ULONG Flag )
{
 // ��ॡ�ࠥ� ���� � ���� ࠡ�祣� �⮫�.
 HENUM Enumeration = WinBeginEnumWindows( QueryDesktopWindow() ); HWND Window = NULLHANDLE;
 while( ( Window = WinGetNextWindow( Enumeration ) ) != NULLHANDLE )
  {
   // ������ ᢮��⢠ ����.
   HSWITCH Switch_handle = WinQuerySwitchHandle( Window, NULLHANDLE );
   SWCNTRL Task = {0}; WinQuerySwitchEntry( Switch_handle, &Task );

   // �᫨ ��� �뫨 ����祭�:
   if( Task.hwnd != NULLHANDLE )
    {
     // �᫨ ���� ������㯭� � ᯨ᪥ ���� - ��祣� ������ �� ����.
     if( Task.uchVisibility != SWL_VISIBLE ) continue;

     // �᫨ ��������� ���� �������⥭ ��� ���� �뫮 ᮧ���� ��㣨� �ਫ������� - ��祣� ������ �� ����.
     if( Task.szSwtitle == NULL || !stristr( WinList_title, Task.szSwtitle ) ) continue;

     // ���塞 ᢮��⢠.
     if( Task.fbJump != Flag )
      {
       Task.fbJump = Flag;
       WinChangeSwitchEntry( Switch_handle, &Task );
      }
    }
  }
 WinEndEnumWindows( Enumeration );

 // ������.
 return;
}

// ��� ������, ����㯭� �� ���� ��� ��४��祭�� �� Alt+Tab ���

// Frame_window - ���� ࠬ��.
ULONG Krnl_WindowList_WindowIsJumpable( HWND Frame_window )
{
 // ������, ���� �� ���� � ᯨ᪥ ����.
 HSWITCH Switch_handle = WinQuerySwitchHandle( Frame_window, NULLHANDLE );

 // �᫨ ��� ����:
 if( Switch_handle != NULLHANDLE )
  {
   // ������ ᢮��⢠ ����.
   SWCNTRL Task = {0}; WinQuerySwitchEntry( Switch_handle, &Task );

   // �᫨ ��� �뫨 ����祭�:
   if( Task.hwnd != NULLHANDLE )
    {
     // �����⥫� �� ������ ��४������� � ������࠭�� �ਫ������.
     if( Task.bProgType == PROG_FULLSCREEN || Task.bProgType == PROG_VDM ) return 0;

     // �����頥� ���祭��.
     if( Task.fbJump == SWL_JUMPABLE ) return 1;
    }
  }

 // ������.
 return 0;
}

// ��� ������, ����㯭� �� ���� ��� ��४��祭�� �� ᯨ᪠ ���� ���

// Frame_window - ���� ࠬ��.
ULONG Krnl_WindowList_WindowIsTouchable( HWND Frame_window )
{
 // ������, ���� �� ���� � ᯨ᪥ ����.
 HSWITCH Switch_handle = WinQuerySwitchHandle( Frame_window, NULLHANDLE );

 // �᫨ ��� ����:
 if( Switch_handle != NULLHANDLE )
  {
   // ������ ᢮��⢠ ����.
   SWCNTRL Task = {0}; WinQuerySwitchEntry( Switch_handle, &Task );

   // �᫨ ��� �뫨 ����祭�:
   if( Task.hwnd != NULLHANDLE )
    {
     // �����⥫� �� ������ ��४������� � ������࠭�� �ਫ������.
     if( Task.bProgType == PROG_FULLSCREEN || Task.bProgType == PROG_VDM ) return 0;

     // �����頥� ���祭��.
     if( Task.uchVisibility == SWL_VISIBLE ) return 1;
    }
  }

 // ������.
 return 0;
}

// ��� ������ �� ���� ����㯭묨 ��� ��४��祭�� ���

// Desktop - ���� ࠡ�祣� �⮫�.
VOID Krnl_WindowList_SetAllWindowsJumpable( HWND Desktop )
{
 // ��ॡ�ࠥ� ���� � ���� ࠡ�祣� �⮫�.
 HENUM Enumeration = WinBeginEnumWindows( Desktop ); HWND Window = NULLHANDLE;
 while( ( Window = WinGetNextWindow( Enumeration ) ) != NULLHANDLE )
  {
   // ��⠭�������� ᢮��⢮.
   if( !Krnl_WindowList_WindowIsJumpable( Window ) ) Krnl_WindowList_SetJumpableFlag( Window, SWL_JUMPABLE );
  }
 WinEndEnumWindows( Enumeration );

 // ������.
 return;
}

// ��� ��室�� ���� � ᯨ᪥ ���� ���

// WinList_title - �������� � ᯨ᪥ ����.
HWND Krnl_WindowList_FindFrameWindowInWindowList( PCHAR WinList_title )
{
 // ���� ����� ���� �� �������.
 HWND Frame_window = NULLHANDLE;

 {
  // ��ॡ�ࠥ� ���� � ���� ࠡ�祣� �⮫�.
  HENUM Enumeration = WinBeginEnumWindows( QueryDesktopWindow() ); HWND Window = NULLHANDLE;
  while( ( Window = WinGetNextWindow( Enumeration ) ) != NULLHANDLE )
   {
    // ������ ᢮��⢠ ����.
    HSWITCH Switch_handle = WinQuerySwitchHandle( Window, NULLHANDLE );
    SWCNTRL Task = {0}; WinQuerySwitchEntry( Switch_handle, &Task );

    // �᫨ ��� �뫨 ����祭�:
    if( Task.hwnd != NULLHANDLE )
     {
      // �᫨ ���� ������㯭� � ᯨ᪥ ���� - ��祣� ������ �� ����.
      if( Task.uchVisibility != SWL_VISIBLE ) continue;

      // �᫨ ��������� ���� �������⥭ - ��祣� ������ �� ����.
      if( Task.szSwtitle == NULL ) continue;

      // �᫨ ��������� ᮤ�ন� �᪮��� ��ப�:
      if( stristr( WinList_title, Task.szSwtitle ) )
       {
        // ���������� ����.
        Frame_window = QueryFrameWindow( Window );

        // �४�頥� ��ॡ�� ����.
        break;
       }
     }
   }
  WinEndEnumWindows( Enumeration );
 }

 // ������.
 return Frame_window;
}

