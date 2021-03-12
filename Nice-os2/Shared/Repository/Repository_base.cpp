#ifdef INCLUDED_BY_SHELL
VOID Repository_QueryExeName (HWND, PCHAR);
#endif

// ��� �஢����, ���� �� ���� "����� ࠡ�祣� �⮫�" ���

// Window - ���� ��� �஢�ન.
BYTE Repository_IsDesktopWindow (HWND Window)
{
  // ������ ���, ��� ����� ��।����� ����.
  CHAR Window_name[SIZE_OF_NAME] = ""; WinQueryClassName (Window, SIZE_OF_NAME, Window_name);

  // �஢��塞 ���.
  if (strc (Window_name, "#32766")) return 1;

  // ������.
  return 0;
}

// ��� �஢����, ���� �� ���� ࠬ��� OS/2 ���

// Window - ���� ��� �஢�ન.
BYTE Repository_IsFrameWindow (HWND Window)
{
  // ������ ���, ��� ����� ��।����� ����.
  CHAR Window_name[SIZE_OF_NAME] = ""; WinQueryClassName (Window, SIZE_OF_NAME, Window_name);

  // �஢��塞 ���.
  {
    // �஢��塞 ���, ��� ����� ��।����� ����.
    BYTE Window_can_be_frame = 0;

    if (strc (Window_name, "#1")) Window_can_be_frame = 1;
    if (strc (Window_name, "EFrame")) Window_can_be_frame = 1;
    if (strc (Window_name, "wpFolder window")) Window_can_be_frame = 1;
    if (strc (Window_name, "Win32FrameClass")) Window_can_be_frame = 1;

    #ifndef INCLUDED_BY_SHELL

    // ����� ��� �ᯮ������� ��� �ᮢ���� ��אַ㣮�쭨���.
    // �᫨ � ���� ��� ��������� � ��� �ᯮ������ �� � ���� ࠡ�祣� �⮫� - �� 㦥 �� ࠬ��.
    if (Window_can_be_frame)
     if (WinWindowFromID (Window, FID_TITLEBAR) == NULLHANDLE)
      if (WinQueryWindow (Window, QW_PARENT) != QueryDesktopWindow ())
       return 0;

    #endif

    // �᫨ �஢�ઠ �ன���� - �� ࠬ��.
    if (Window_can_be_frame) return 1;
  }

  // ������.
  return 0;
}

// ��� �஢����, ���� �� ���� ࠬ��� WPS ���

// Frame_window - ���� ��� �஢�ન.
BYTE Repository_IsFolderWindow (HWND Frame_window)
{
  // ������ ���, ��� ����� ��।����� ����.
  CHAR Window_name[SIZE_OF_NAME] = ""; WinQueryClassName (Frame_window, SIZE_OF_NAME, Window_name);

  // �஢��塞 ���.
  if (strc (Window_name, "wpFolder window")) return 1;

  // ������.
  return 0;
}

// ��� �஢����, ���� �� ������ ���� ���

// Window - ���� ��� �஢�ન.
BYTE Repository_IsMenuWindow (HWND Window)
{
  // ������ ���, ��� ����� ��।����� ����.
  CHAR Window_name[SIZE_OF_NAME] = ""; WinQueryClassName (Window, SIZE_OF_NAME, Window_name);

  // �஢��塞 ���.
  if (strc (Window_name, "#4")) return 1;

  // ������.
  return 0;
}

// ��� �஢����, ���� �� ���� ���������� ���

// Window - ���� ��� �஢�ન.
BYTE Repository_IsTitleBarWindow (HWND Window)
{
  // ������ ���, ��� ����� ��।����� ����.
  CHAR Window_name[SIZE_OF_NAME] = ""; WinQueryClassName (Window, SIZE_OF_NAME, Window_name);

  // �஢��塞 ���.
  if (strc (Window_name, "#9")) return 1;

  // ������.
  return 0;
}

// ��� �஢����, ���� �� ���� ����᪮� ��ᬮ�� ���

// Window - ���� ��� �஢�ન.
BYTE Repository_IsScrollBarWindow (HWND Window)
{
  // ������ ���, ��� ����� ��।����� ����.
  CHAR Window_name[SIZE_OF_NAME] = ""; WinQueryClassName (Window, SIZE_OF_NAME, Window_name);

  // �஢��塞 ���.
  if (strc (Window_name, "#8")) return 1;

  // ������.
  return 0;
}

// ��� �஢����, ���� �� ���� ����� ����� ���

// Window - ���� ��� �஢�ન.
BYTE Repository_IsInputFieldWindow (HWND Window)
{
  // ������ ���, ��� ����� ��।����� ����.
  CHAR Window_name[SIZE_OF_NAME] = ""; WinQueryClassName (Window, SIZE_OF_NAME, Window_name);

  // �஢��塞 ���.
  if (strc (Window_name, "#10") ||
      strstr ("MultiLineEntryField", Window_name)) return 1;

  // ������.
  return 0;
}

// ��� �஢����, ���� �� ���� ��������� ����� ����� ���

// Window - ���� ��� �஢�ન.
BYTE Repository_IsEntryFieldWindow (HWND Window)
{
  // ������ ���, ��� ����� ��।����� ����.
  CHAR Window_name[SIZE_OF_NAME] = ""; WinQueryClassName (Window, SIZE_OF_NAME, Window_name);

  // �஢��塞 ���.
  if (strc (Window_name, "#6") ||
      strstr ("EntryField", Window_name)) return 1;

  // ������.
  return 0;
}

// ��� �஢����, ���� �� ���� ᯨ᪮� � ���窠�� ���

// Window - ���� ��� �஢�ન.
BYTE Repository_IsIconViewWindow (HWND Window)
{
  // ������ ���, ��� ����� ��।����� ����.
  CHAR Window_name[SIZE_OF_NAME] = ""; WinQueryClassName (Window, SIZE_OF_NAME, Window_name);

  // �஢��塞 ���.
  if (strc (Window_name, "#37")) return 1;

  // ������.
  return 0;
}

// ��� �஢����, ���� �� ���� ᯨ᪮� � ���窠�� ���

// Window - ���� ��� �஢�ન.
BYTE Repository_IsDetailViewWindow (HWND Window)
{
  // ������ ���, ��� ����� ��।����� ����.
  CHAR Window_name[SIZE_OF_NAME] = ""; WinQueryClassName (Window, SIZE_OF_NAME, Window_name);

  // �஢��塞 ���.
  if (strc (Window_name, "#50")) return 1;
  if (strc (Window_name, "#51")) return 1;

  // ������.
  return 0;
}

// ��� �஢����, ���� �� ���� ᯨ᪮� � �믠���騬 ���� ���

// Window - ���� ��� �஢�ન.
BYTE Repository_IsComboBoxWindow (HWND Window)
{
  // ������ ���, ��� ����� ��।����� ����.
  CHAR Window_name[SIZE_OF_NAME] = ""; WinQueryClassName (Window, SIZE_OF_NAME, Window_name);

  // �஢��塞 ���.
  if (strc (Window_name, "#2") ||
      strstr ("Combo", Window_name) ||
      strstr ("DropDown", Window_name)) return 1;

  // ������.
  return 0;
}

// ��� �஢����, ���� �� ���� ᯨ᪮� ���

// Window - ���� ��� �஢�ન.
BYTE Repository_IsListBoxWindow (HWND Window)
{
  // ������ ���, ��� ����� ��।����� ����.
  CHAR Window_name[SIZE_OF_NAME] = ""; WinQueryClassName (Window, SIZE_OF_NAME, Window_name);

  // �஢��塞 ���.
  if (strc (Window_name, "#7") ||
      strstr ("ListBox", Window_name)) return 1;

  // ������.
  return 0;
}

// ��� �஢����, ���� �� ���� ��������� ᯨ᪮� ���

// Window - ���� ��� �஢�ન.
BYTE Repository_IsSpinButtonWindow (HWND Window)
{
  // ������ ���, ��� ����� ��।����� ����.
  CHAR Window_name[SIZE_OF_NAME] = ""; WinQueryClassName (Window, SIZE_OF_NAME, Window_name);

  // �஢��塞 ���.
  if (strc (Window_name, "#32") ||
      strstr ("SpinButton", Window_name)) return 1;

  // ������.
  return 0;
}

// ��� �஢����, ���� �� ���� �⬥砥��� ������� ���

// Window - ���� ��� �஢�ન.
BYTE Repository_IsCheckBoxButtonWindow (HWND Window)
{
  // ������ ���, ��� ����� ��।����� ����.
  CHAR Window_name[SIZE_OF_NAME] = ""; WinQueryClassName (Window, SIZE_OF_NAME, Window_name);

  // �஢��塞 ���.
  if (strc (Window_name, "#3") ||
      strstr ("CheckBox", Window_name))
  {
    QMSG Report = {0};
    LONG Style = (LONG) WinSendMsg (Window, WM_QUERYDLGCODE, &Report, 0);
    if (Style & DLGC_CHECKBOX) return 1;
  }

  // ������.
  return 0;
}

// ��� �஢����, ���� �� ���� �롨ࠥ��� ������� ���

// Window - ���� ��� �஢�ન.
BYTE Repository_IsRadioButtonWindow (HWND Window)
{
  // ������ ���, ��� ����� ��।����� ����.
  CHAR Window_name[SIZE_OF_NAME] = ""; WinQueryClassName (Window, SIZE_OF_NAME, Window_name);

  // �஢��塞 ���.
  if (strc (Window_name, "#3") ||
      strstr ("RadioButton", Window_name))
  {
    QMSG Report = {0};
    LONG Style = (LONG) WinSendMsg (Window, WM_QUERYDLGCODE, &Report, 0);
    if (Style & DLGC_RADIOBUTTON) return 1;
  }

  // ������.
  return 0;
}

// ��� �஢����, ���� �� ���� ������� ���

// Window - ���� ��� �஢�ન.
BYTE Repository_IsButtonWindow (HWND Window)
{
  // ������ ���, ��� ����� ��।����� ����.
  CHAR Window_name[SIZE_OF_NAME] = ""; WinQueryClassName (Window, SIZE_OF_NAME, Window_name);

  // �஢��塞 ���.
  if (strc (Window_name, "#3") ||
      strstr ("PushButton", Window_name))
  {
    QMSG Report = {0};
    LONG Style = (LONG) WinSendMsg (Window, WM_QUERYDLGCODE, &Report, 0);
    if (Style & DLGC_PUSHBUTTON || Style & DLGC_DEFAULT) return 1;
  }

  // ������.
  return 0;
}

// ��� �஢����, ���� �� ���� ������� ���

// Window - ���� ��� �஢�ન.
BYTE Repository_IsSliderWindow (HWND Window)
{
  // ������ ���, ��� ����� ��।����� ����.
  CHAR Window_name[SIZE_OF_NAME] = ""; WinQueryClassName (Window, SIZE_OF_NAME, Window_name);

  // �஢��塞 ���.
  if (strc (Window_name, "#38")) return 1;

  // ������.
  return 0;
}

// ��� �஢����, ���� �� ���� ��㣫� ������� ���

// Window - ���� ��� �஢�ન.
BYTE Repository_IsCircularSliderWindow (HWND Window)
{
  // ������ ���, ��� ����� ��।����� ����.
  CHAR Window_name[SIZE_OF_NAME] = ""; WinQueryClassName (Window, SIZE_OF_NAME, Window_name);

  // �஢��塞 ���.
  if (strc (Window_name, "#65")) return 1;

  // ������.
  return 0;
}

// ��� �஢����, ���� �� ���� ����஬ �������� ���

// Window - ���� ��� �஢�ન.
BYTE Repository_IsNotebookWindow (HWND Window)
{
  // ������ ���, ��� ����� ��।����� ����.
  CHAR Window_name[SIZE_OF_NAME] = ""; WinQueryClassName (Window, SIZE_OF_NAME, Window_name);

  // �஢��塞 ���.
  if (strc (Window_name, "#40")) return 1;

  // ������.
  return 0;
}

// ��� �஢����, ���� �� ���� ��������� ���

// Window - ���� ��� �஢�ન.
BYTE Repository_IsNotebookPageWindow (HWND Window)
{
  // �������� - ���� ࠬ�� ��� ���������, �ᯮ�������� � ����� ��������.
  if (Repository_IsFrameWindow (Window))
   if (WinWindowFromID (Window, FID_TITLEBAR) == NULLHANDLE)
    if (Repository_IsNotebookWindow (WinQueryWindow (Window, QW_PARENT)))
     return 1;

  // ������.
  return 0;
}

// ��� �஢����, ���� �� ���� �������� ��אַ㣮�쭨��� ���

// Window - ���� ��� �஢�ન.
BYTE Repository_IsStaticWindow (HWND Window)
{
  // ������ ���, ��� ����� ��।����� ����.
  CHAR Window_name[SIZE_OF_NAME] = ""; WinQueryClassName (Window, SIZE_OF_NAME, Window_name);

  // �஢��塞 ���.
  if (strc (Window_name, "#5"))
   if (WinQueryWindowTextLength (Window) == 0)
    return 1;

  // ������.
  return 0;
}

// ��� �஢����, ���� �� ���� �������� ���

// Window - ���� ��� �஢�ન.
BYTE Repository_IsLabelWindow (HWND Window)
{
  // ������ ���, ��� ����� ��।����� ����.
  CHAR Window_name[SIZE_OF_NAME] = ""; WinQueryClassName (Window, SIZE_OF_NAME, Window_name);

  // �஢��塞 ���.
  if (strc (Window_name, "#5"))
   if (WinQueryWindowTextLength (Window) != 0)
    return 1;

  // ������.
  return 0;
}

// ��� �஢����, ����� �� ���� ���� �����窮� ��� ����� ����� ���

// Window - ���� ��� �஢�ન.
BYTE Repository_IsInputFieldContainerWindow (HWND Window)
{
  // ���� ����� ����� �ᯮ�������� � ��אַ㣮�쭨��� � � ���������.
  if (Repository_IsStaticWindow (Window) ||
      Repository_IsNotebookWindow (Window) ||
      Repository_IsNotebookPageWindow (Window)) return 1;

  // ������.
  return 0;
}

// ��� �஢����, ����� �� ������ ���� ���� ����� FileBar ���

// Frame_window - ���� ��� �஢�ન.
BYTE Repository_IsFileBarWindow (HWND Frame_window)
{
  // ������ ���� ࠡ�祩 ������.
  HWND Client_window = WinWindowFromID (Frame_window, FID_CLIENT);

  if (Client_window != NULLHANDLE)
  {
    // ������ ���, ��� ����� ��।����� ����.
    CHAR Client_name[SIZE_OF_NAME] = ""; WinQueryClassName (Client_window, SIZE_OF_NAME, Client_name);

    // �஢��塞 ���.
    if (strc (Client_name, "FileBar")) return 1;
  }

  // ������.
  return 0;
}

// ��� �஢����, ���� �� ���� ࠬ��� MDesk ���

// Frame_window - ���� ��� �஢�ન.
BYTE Repository_IsMDeskWindow (HWND Frame_window)
{
  // ������ ���� ࠡ�祩 ������.
  HWND Client_window = WinWindowFromID (Frame_window, FID_CLIENT);

  if (Client_window != NULLHANDLE)
  {
    // ������ ���, ��� ����� ��।����� ����.
    CHAR Client_name[SIZE_OF_NAME] = ""; WinQueryClassName (Client_window, SIZE_OF_NAME, Client_name);

    // �஢��塞 ���.
    if (strc (Client_name, "MDesk-Folder")) return 1;
  }

  // ������.
  return 0;
}

// ��� �஢����, ����� �� ������ ���� ���� ����� WindowList ���

// Frame_window - ����, ���஥ ���� �஢����.
BYTE Repository_IsWinListWindow (HWND Frame_window)
{
  // ������ ���� ࠡ�祩 ������.
  HWND Client_window = WinWindowFromID (Frame_window, FID_CLIENT);

  if (Client_window != NULLHANDLE)
  {
    // ������ ���, ��� ����� ��।����� ����.
    CHAR Client_name[SIZE_OF_NAME] = ""; WinQueryClassName (Client_window, SIZE_OF_NAME, Client_name);

    // �஢��塞 ���.
    if (strc (Client_name, "WindowList")) return 1;
  }

  // ������.
  return 0;
}

// ��� �஢����, ���� �� ���� ࠬ��� VIO ���

// Frame_window - ���� ��� �஢�ન.
BYTE Repository_IsVIOWindow (HWND Frame_window)
{
  // ������ ���� ࠡ�祩 ������.
  HWND Client_window = WinWindowFromID (Frame_window, FID_CLIENT);

  if (Client_window != NULLHANDLE)
  {
    // ������ ���, ��� ����� ��।����� ����.
    CHAR Client_name[SIZE_OF_NAME] = ""; WinQueryClassName (Client_window, SIZE_OF_NAME, Client_name);

    // �஢��塞 ���.
    if (strc (Client_name, "Shield")) return 1;
  }

  // ������.
  return 0;
}

// ��� �஢����, ���� �� ���� ࠬ��� Win-OS/2 ��� Odin ���

// Frame_window - ���� ࠬ��.
BYTE Repository_IsWindowsWindow (HWND Frame_window)
{
  // ������ ���� ࠡ�祩 ������.
  HWND Client_window = WinWindowFromID (Frame_window, FID_CLIENT);

  if (Client_window != NULLHANDLE)
  {
    // ������ ���, ��� ����� ��।����� ����.
    CHAR Client_name[SIZE_OF_NAME] = ""; WinQueryClassName (Client_window, SIZE_OF_NAME, Client_name);

    // �஢��塞 ���.
    if (strstr ("Win32WindowClass", Client_name)) return 1;
    if (strc (Client_name, "SeamlessClass")) return 1;
  }

  // ������.
  return 0;
}

// ��� �஢����, ᮧ���� �� ���� �����窮� OS/2 (� ���� PM, �� WPS � �� �ਫ�����ﬨ) ���

// Frame_window - ����, ���஥ ���� �஢����.
BYTE Repository_IsPMShellAuxiliaryWindow (HWND Frame_window)
{
  // ���� VIO � Win-OS/2 �� ��⠥� ������ Presentation Manager: ��� ��� �
  // ᮧ������ �����窮�, �� � ��� ࠡ���� �ਫ������, �� �� ���� �����窨.
  if (Repository_IsVIOWindow (Frame_window) || Repository_IsWindowsWindow (Frame_window)) return 0;

  // ������ �ਫ������, ᮧ���襥 ����.
  PID Process_ID = 0; TID Thread_ID = 0; WinQueryWindowProcess (Frame_window, &Process_ID, &Thread_ID);

  // �᫨ ��� �� 㤠���� 㧭��� - ��⠥�, �� ���� ᮧ���� �����窮� Presentation Manager.
  // ��� �ࠢ���, �� �� �� ��⮢�� ⥪�⮢�� ���� ��� ���� ������� � ⥪�⮢� ᮮ�饭���.
  if (Process_ID == 0) return 1;

  // ������ �ਫ������, ᮧ���襥 ���� ࠡ�祣� �⮫�.
  PID Desktop_process_ID = 0; TID Desktop_thread_ID = 0; WinQueryWindowProcess (QueryDesktopWindow (), &Desktop_process_ID, &Desktop_thread_ID);

  // �᫨ ���祭�� ᮢ������ - ���� ᮧ���� �����窮� Presentation Manager.
  if (Desktop_process_ID != 0 && Process_ID == Desktop_process_ID) return 1;

  // ������.
  return 0;
}

// ��� �஢����, ᮧ���� �� ���� �����窮� ࠡ�祣� �⮫� (WPS, �� PM) ���

// Frame_window - ����, ���஥ ���� �஢����.
BYTE Repository_IsWorkplaceShellWindow (HWND Frame_window)
{
  // �᫨ �� ���� VIO ��� Win-OS/2 - ������.
  if (Repository_IsVIOWindow (Frame_window) || Repository_IsWindowsWindow (Frame_window)) return 0;

  // �᫨ �� ���� ᮧ���� ᠬ�� �����窮� Presentation Manager - ������.
  if (Repository_IsPMShellAuxiliaryWindow (Frame_window)) return 0;

  // �᫨ �� ���� 䮫��� - � �� ���� �����窨 WPS, � �஢�ન �� �ॡ�����.
  if (Repository_IsFolderWindow (Frame_window)) return 1;

  // ������ ��� �ਫ������, �ᯮ��㥬��� � ����⢥ �����窨.
  PCHAR Workplace = NULL; DosScanEnv ("RUNWORKPLACE", (PPCSZ) &Workplace);

  // �᫨ ��� �������⭮ - ��� �� ������ ����, ���஥ ����� ���� �� ᮧ����, ������.
  if (Workplace == NULL) return 0;

  // ������ ��� �ਫ������, ᮧ���襣� ����.
  CHAR Exe_name[SIZE_OF_NAME] = "";

  #ifndef INCLUDED_BY_SHELL
  GetDetectedExeName (Frame_window, Exe_name);
  #else
  Repository_QueryExeName (Frame_window, Exe_name);
  #endif

  // �᫨ ��� 㤠���� ��।�����:
  if (Exe_name[0] != 0)
  {
    // �஢��塞 ���.
    if (stristr (Exe_name, Workplace)) return 1;
  }
  // � �᫨ ��� �������⭮:
  else
  {
    // �� ����� ���� �� 㣮���, �� �� ���� �� ���� �����窨.
    return 0;
  }

  // ������.
  return 0;
}

// ��� �஢����, ����� �� ������ ���� ���� ��४���⥫�� ���� �� "Alt + Tab" ���

// Frame_window - ����, ���஥ ���� �஢����.
BYTE Repository_IsAltTabSwitcherWindow (HWND Frame_window)
{
  // ������ ���, ��� ����� ��।����� ����.
  CHAR Window_name[SIZE_OF_NAME] = ""; WinQueryClassName (Frame_window, SIZE_OF_NAME, Window_name);

  // �஢��塞 ���.
  if (stric (Window_name, "AltTabSwitcher")) return 1;

  // ������.
  return 0;
}

// ��� �஢����, ����� �� ������ ���� ���� ����� lSwitcher ���

// Frame_window - ����, ���஥ ���� �஢����.
BYTE Repository_IslSwitcherWindow (HWND Frame_window)
{
  // ������ ���� ࠡ�祩 ������.
  HWND Client_window = WinWindowFromID (Frame_window, FID_CLIENT);

  if (Client_window != NULLHANDLE)
  {
    // ������ ���, ��� ����� ��।����� ����.
    CHAR Client_name[SIZE_OF_NAME] = ""; WinQueryClassName (Client_window, SIZE_OF_NAME, Client_name);

    // �஢��塞 ���. ��砫� �����, "lsw" ����� ���� ������ ࠧ�묨 �㪢���.
    if (stric (Client_name, "lswPopupClass")) return 1;
    if (stric (Client_name, "lswTaskBarClass")) return 1;
  }

  // ������.
  return 0;
}

// ��� �஢����, ����� �� ���� �ᯮ�������, ��宦�� �� WarpCenter ���

// Window - ���� ��� �஢�ન.
BYTE Repository_HasWarpCenterSize (HWND Window)
{
  // ������ ࠧ��� ����.
  RECT Rectangle = {0}; WinQueryWindowRect (Window, &Rectangle);

  // �᫨ �ਭ� ���� � ��᪮�쪮 ࠧ ����� ��� �����:
  if (Rectangle.xRight > Rectangle.yTop * 10)
  {
    // ������ ���� ࠡ�祣� �⮫�.
    HWND Desktop = QueryDesktopWindow ();

    // ������ ࠧ��� �࠭�.
    INT X_Screen = WinQuerySysValue (QueryDesktopWindow (), SV_CXSCREEN);

    // �᫨ �ਭ� ���� ����� ࠧ��� �࠭� - �� ���� ��宦� �� WarpCenter.
    if (Rectangle.xRight > X_Screen - 10) return 1;
  }

  // ������.
  return 0;
}

// ��� �஢����, ����� �� ������ ���� ���� ����� WarpCenter ���

// Window - ����, ���஥ ���� �஢����.
BYTE Repository_IsWarpCenterWindow (HWND Window)
{
  // �᫨ ���� ᮧ���� �� �����窮� - ������.
  if (!Repository_IsWorkplaceShellWindow (Window)) return 0;

  // �᫨ த�⥫�᪮� ���� �� ࠡ�稩 �⮫ - ������.
  if (WinQueryWindow (Window, QW_PARENT) != QueryDesktopWindow ()) return 0;

  // ������ ���, ��� ����� ��।����� ����.
  CHAR Window_name[SIZE_OF_NAME] = ""; WinQueryClassName (Window, SIZE_OF_NAME, Window_name);

  // �᫨ �� ����� ���� WarpCenter:
  if (strc (Window_name, "#3"))
   if (Repository_HasWarpCenterSize (Window))
   {
     // ������ ��������� ����.
     Window_name[0] = NULL;
     WinQueryWindowText (Window, SIZE_OF_NAME, Window_name);

     // �᫨ �� WarpCenter - �����頥� 1.
     if (strc (Window_name, "SmartCenter")) return 1;
   }

  // ������.
  return 0;
}

// ��� �஢����, ����� �� ������ ���� ���� ����� ���� WarpCenter ���

// Window - ����, ���஥ ���� �஢����.
BYTE Repository_IsWarpCenterMenuWindow (HWND Window)
{
  // �᫨ ���� ᮧ���� �� �����窮� - ������.
  if (!Repository_IsWorkplaceShellWindow (Window)) return 0;

  // �᫨ த�⥫�᪮� ���� �� ࠡ�稩 �⮫ - ������.
  if (WinQueryWindow (Window, QW_PARENT) != QueryDesktopWindow ()) return 0;

  // ������ ���, ��� ����� ��।����� ����.
  CHAR Window_name[SIZE_OF_NAME] = ""; WinQueryClassName (Window, SIZE_OF_NAME, Window_name);

  // �᫨ �� ����� ���� WarpCenter:
  if (strc (Window_name, "#3"))
  {
    // ������ ࠧ��� ����.
    RECT Rectangle = {0}; WinQueryWindowRect (Window, &Rectangle);

    // �᫨ ���� ���� ����� ��� �ਭ� - �� ���� WarpCenter.
    if (Rectangle.yTop > Rectangle.xRight) return 1;
  }

  // ������.
  return 0;
}

// ��� �஢����, ����� �� ������ ���� ���� ����� SysTray ���

// Window - ����, ���஥ ���� �஢����.
BYTE Repository_IsSysTrayWindow (HWND Window)
{
  // ������ ���� ࠡ�祩 ������.
  HWND Client_window = WinWindowFromID (Window, FID_CLIENT);

  if (Client_window != NULLHANDLE)
  {
    // ������ ���, ��� ����� ��।����� ����.
    CHAR Client_name[SIZE_OF_NAME] = ""; WinQueryClassName (Client_window, SIZE_OF_NAME, Client_name);

    // �᫨ ��� ����� ���� ����� SysTray:
    if (stristr ("SysTray", Client_name))
    {
      // �஢��塞 �ᯮ������� ����.
      if (Repository_HasWarpCenterSize (Window)) return 1;
    }
  }

  // ������.
  return 0;
}

// ��� �஢����, ����� �� ������ ���� ���� ����� ���� SysTray ���

// Window - ����, ���஥ ���� �஢����.
BYTE Repository_IsSysTrayMenuWindow (HWND Window)
{
  // �᫨ �� ���� ����:
  if (Repository_IsMenuWindow (Window))
  {
    // ������ ���� ��������.
    HWND Owner_window = WinQueryWindow (Window, QW_OWNER);

    // ������ ���, ��� ����� ��।����� ����.
    CHAR Owner_name[SIZE_OF_NAME] = ""; WinQueryClassName (Owner_window, SIZE_OF_NAME, Owner_name);

    // �஢��塞 ���.
    if (strc (Owner_name, "AgentCenterClass")) return 1;
    if (strc (Owner_name, "SPLG_WarpButton")) return 1;
  }

  // ������.
  return 0;
}

// ��� �஢����, ����� �� ������ ���� ���� ����� XWP TaskBar ���

// Window - ����, ���஥ ���� �஢����.
BYTE Repository_IsXWPTaskBarWindow (HWND Window)
{
  // ������ ���� ࠡ�祩 ������.
  HWND Client_window = WinWindowFromID (Window, FID_CLIENT);

  if (Client_window != NULLHANDLE)
  {
    // ������ ���, ��� ����� ��।����� ����.
    CHAR Client_name[SIZE_OF_NAME] = ""; WinQueryClassName (Client_window, SIZE_OF_NAME, Client_name);

    // �᫨ ��� ����� ���� ����� XWP TaskBar:
    if (stristr ("XWPCenter", Client_name))
    {
      // �஢��塞 �ᯮ������� ����.
      if (Repository_HasWarpCenterSize (Window)) return 1;
    }
  }

  // ������.
  return 0;
}

// ��� �஢����, ����� �� ������ ���� ���� ����� ���� XWP TaskBar ���

// Window - ����, ���஥ ���� �஢����.
BYTE Repository_IsXWPTaskBarMenuWindow (HWND Window)
{
  // �᫨ �� ���� ����:
  if (Repository_IsMenuWindow (Window))
  {
    // ������ ���� ��������.
    HWND Owner_window = WinQueryWindow (Window, QW_OWNER);

    // ������ ���, ��� ����� ��।����� ����.
    CHAR Owner_name[SIZE_OF_NAME] = ""; WinQueryClassName (Owner_window, SIZE_OF_NAME, Owner_name);

    // �஢��塞 ���.
    if (stristr ("XWPCenter", Owner_name)) return 1;
  }

  // ������.
  return 0;
}

// ��� �஢����, ����� �� ������ ���� ���� ����� XWP Pager ���

// Window - ����, ���஥ ���� �஢����.
BYTE Repository_IsXWPPagerWindow (HWND Frame_window)
{
  // ������ ���� ࠡ�祩 ������.
  HWND Client_window = WinWindowFromID (Frame_window, FID_CLIENT);

  if (Client_window != NULLHANDLE)
  {
    // ������ ���, ��� ����� ��।����� ����.
    CHAR Client_name[SIZE_OF_NAME] = ""; WinQueryClassName (Client_window, SIZE_OF_NAME, Client_name);

    // �஢��塞 ���.
    if (stristr ("XWPXPagerClient", Client_name)) return 1;
  }

  // ������.
  return 0;
}

// ��� �஢����, ����� �� ������ ���� ���� ����� SafeFire ���

// Window - ����, ���஥ ���� �஢����.
BYTE Repository_IsSafeFireWindow (HWND Frame_window)
{
  // ������ ���� ࠡ�祩 ������.
  HWND Client_window = WinWindowFromID (Frame_window, FID_CLIENT);

  if (Client_window != NULLHANDLE)
  {
    // ������ ���, ��� ����� ��।����� ����.
    CHAR Client_name[SIZE_OF_NAME] = ""; WinQueryClassName (Client_window, SIZE_OF_NAME, Client_name);

    // �஢��塞 ���.
    if (stristr ("Uni.Cell.Client", Client_name)) return 1;
  }

  // ������.
  return 0;
}

// ��� �஢����, ����� �� ������ ���� ���� ����� ��⥬���� ᮮ�饭�� ���

// Frame_window - ����, ���஥ ���� �஢����.
BYTE Repository_IsSysMsgWindow (HWND Frame_window)
{
  // ������ ���� ࠡ�祩 ������.
  HWND Client_window = WinWindowFromID (Frame_window, FID_CLIENT);

  if (Client_window != NULLHANDLE)
  {
    // ������ ���, ��� ����� ��।����� ����.
    CHAR Client_name[SIZE_OF_NAME] = ""; WinQueryClassName (Client_window, SIZE_OF_NAME, Client_name);

    // �஢��塞 ���.
    if (strc (Client_name, "PM Hard Error")) return 1;
  }

  // ������.
  return 0;
}

