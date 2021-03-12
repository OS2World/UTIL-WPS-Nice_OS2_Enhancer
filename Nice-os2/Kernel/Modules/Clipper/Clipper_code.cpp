
// ��� ������, ���� �� �뤥����� � ⥪�⮢�� ���� ���

// Frame_window - ⥪�⮢�� ����.
BYTE Clipper_VIOMarkingIsInProcess (HWND Frame_window)
{
  // ������ ���� ���⨭��.
  HWND SysMenu_window = WinWindowFromID (Frame_window, FID_SYSMENU);

  // �᫨ ��ப� ���� ��� ����祭�� �뤥����� ���� ��� � ��࠭� - � ���� ���� �뤥�����.
  if (MenuItemIsPresent (SysMenu_window, SM_VIO_MARK))
   if (MenuItemIsChecked (SysMenu_window, SM_VIO_MARK))
    return 1;

  // ������.
  return 0;
}

// ��� ��⠢��� ⥪�� � ���� ���

// Frame_window - ⥪�⮢�� ����.
VOID Clipper_PasteTextToVIOWindow (HWND Frame_window)
{
  // �᫨ � Clipboard ���� �����-� ��ப�:
  CHAR Short_string[4] = ""; GetStringFromClipboard (Enhancer.Application, Short_string, 4);

  if (Short_string[0] != 0)
  {
    // ����뢠�� Clipboard � ���������� ��ப� �� ࠧ ��� CF_TEXT.
    // �� ����室��� ������ ��⮬�, �� �᫨ ��ப� �뫨 ����� �� ��㣮�� ⥪�⮢��� ����,
    // � �� ����⮩ ������ Shift ��㣨� ⥪�⮢� ���� �� ����� ��⠢��� ��᫥���� �㪢�.

    // �⢮��� ������ ��� ⥪��.
    PCHAR Clipboard_text = NULL; INT Length = 16384;
    if (DosAllocMem ((PPVOID) &Clipboard_text, Length, PAG_ALLOCATE) != NO_ERROR) return;

    // ����ࠥ� ⥪�� �� Clipboard � ��� �� ������塞 ��� � Clipboard.
    GetStringFromClipboard (Enhancer.Application, Clipboard_text, Length); PutStringIntoClipboard (Enhancer.Application, Clipboard_text);

    // �᢮������� ������.
    DosFreeMem (Clipboard_text); Clipboard_text = NULL;

    // ������ ���� ���⨭��.
    HWND SysMenu_window = WinWindowFromID (Frame_window, FID_SYSMENU);

    // �᫨ � ���� ���� ��ப� ��� ��⠢�� ⥪�� - ���뫠�� � ���� ������� �� ���.
    if (MenuItemIsPresent (SysMenu_window, SM_VIO_PASTE))
     WinPostMsg (Frame_window, WM_SYSCOMMAND, (MPARAM) SM_VIO_PASTE, MPFROM2SHORT (CMDSRC_MENU, 0));
  }

  // ������.
  return;
}

// ��� �몫�砥� �뤥����� ��ப � ⥪�⮢�� ���� ���

// Frame_window - ⥪�⮢�� ����.
VOID Clipper_EndVIOMarkingAndCopyText (HWND Frame_window)
{
  // ������ ���� ���⨭��.
  HWND SysMenu_window = WinWindowFromID (Frame_window, FID_SYSMENU);

  // �᫨ ���� ��� - ������.
  if (!WinIsWindow (WinQueryAnchorBlock (SysMenu_window), SysMenu_window)) return;

  // �᫨ � ���� ���� ��ப� ��� ����祭�� �뤥�����:
  if (MenuItemIsPresent (SysMenu_window, SM_VIO_MARK) &&
      MenuItemIsPresent (SysMenu_window, SM_VIO_MOUSE))
  {
    // �᫨ ��� ��ப� ���� ��� ����祭�� �뤥����� ��࠭�:
    if (MenuItemIsChecked (SysMenu_window, SM_VIO_MARK) &&
        MenuItemIsChecked (SysMenu_window, SM_VIO_MOUSE))
    {
      // ���������� �뤥����� ⥪��. �� �⮬ ��ப� ��� ����祭�� �뤥����� ������ ������� ���� ����祭���.
      if (MenuItemIsPresent (SysMenu_window, SM_VIO_COPY))
       WinSendMsg (Frame_window, WM_SYSCOMMAND, (MPARAM) SM_VIO_COPY, MPFROM2SHORT (CMDSRC_MENU, 0));

      // �몫�砥� �뤥����� � ������� ���.
      WinSendMsg (Frame_window, WM_SYSCOMMAND, (MPARAM) SM_VIO_MOUSE, MPFROM2SHORT (CMDSRC_MENU, 0));
      WinSendMsg (SysMenu_window, MM_SETITEMATTR, MPFROM2SHORT (SM_VIO_MOUSE, INCLUDE_SUBMENUS), MPFROM2SHORT (MIA_CHECKED, 0));

      // �᫨ ��ப� ���� ��� ����祭�� �뤥����� �� �� ��࠭�:
      if (MenuItemIsChecked (SysMenu_window, SM_VIO_MARK))
      {
        // �몫�砥� �뤥����� � ������� ����������.
        WinSendMsg (Frame_window, WM_SYSCOMMAND, (MPARAM) SM_VIO_MARK, MPFROM2SHORT (CMDSRC_MENU, 0));
        WinSendMsg (SysMenu_window, MM_SETITEMATTR, MPFROM2SHORT (SM_VIO_MARK, INCLUDE_SUBMENUS), MPFROM2SHORT (MIA_CHECKED, 0));
      }
    }
  }

  // ������.
  return;
}

// ��� ��⠢��� ⥪�� � ���� Mozilla �� ����⨨ FireFox-������ ���

// Input_window - ����, Command - ����� �㪢� ���� ��⠢���.
VOID Clipper_PasteFireFoxCharacters (HWND Input_window, ULONG Command)
{
  // ���������� ᮤ�ন��� Clipboard. ��� ࠡ��� � FireFox �ॡ���� �� ⮫쪮
  // ��몭������� ⥪��, �� � ⥪�� � ����஢�� UCS2, ������ �������� Mozilla.
  if (Clipper.RTSettings.Clipboard_data_Text != NULL) { DosFreeMem (Clipper.RTSettings.Clipboard_data_Text); Clipper.RTSettings.Clipboard_data_Text = NULL; }
  if (Clipper.RTSettings.Clipboard_data_UCS2 != NULL) { DosFreeMem (Clipper.RTSettings.Clipboard_data_UCS2); Clipper.RTSettings.Clipboard_data_UCS2 = NULL; }

  {
    Clipper.RTSettings.Clipboard_data_Text_length = 0;
    Clipper.RTSettings.Clipboard_data_UCS2_length = 0;

    INT Max_length = 16384; PBYTE Text = NULL;
    if (DosAllocMem ((PPVOID) &Text, Max_length, PAG_ALLOCATE) != NO_ERROR) return;

    GetStringFromClipboard (Enhancer.Application, Text, Max_length);
    INT Real_length = strlen (Text) + 1;

    DosFreeMem (Text); Text = NULL;

    Clipper.RTSettings.Clipboard_data_Text_length = Real_length;
    Clipper.RTSettings.Clipboard_data_UCS2_length = Real_length * 2;
  }

  if (DosAllocMem ((PPVOID) &Clipper.RTSettings.Clipboard_data_Text, Clipper.RTSettings.Clipboard_data_Text_length, PAG_ALLOCATE) != NO_ERROR) return;
  if (DosAllocMem ((PPVOID) &Clipper.RTSettings.Clipboard_data_UCS2, Clipper.RTSettings.Clipboard_data_UCS2_length, PAG_ALLOCATE) != NO_ERROR) return;

  bzero (Clipper.RTSettings.Clipboard_data_Text, Clipper.RTSettings.Clipboard_data_Text_length);
  bzero (Clipper.RTSettings.Clipboard_data_UCS2, Clipper.RTSettings.Clipboard_data_UCS2_length);

  CHAR Mozilla_internal_format[] = "text/unicode";

  GetStringFromClipboard (Enhancer.Application,
                          Clipper.RTSettings.Clipboard_data_Text,
                          Clipper.RTSettings.Clipboard_data_Text_length,
                          Clipper.RTSettings.Clipboard_data_UCS2,
                          Clipper.RTSettings.Clipboard_data_UCS2_length,
                          Mozilla_internal_format);

  // ������ ����� ��ப� � ���筮� ���� � � ���� UCS2-��ப�.
  BYTE Common_string[3] = { 0x00, 0x00, 0x00 };
  BYTE UCS2LittleEndian_string[6] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
  LONG UCS2LittleEndian_string_length = 0;

  #include "Modules\\Clipper\\Clipper_ffx.cpp"

  if (Command == SM_FFX_PASTE_DASH)
  {
    Common_string[0] = '-';
    Common_string[1] = 0x00;

    UCS2LittleEndian_string[0] = Dash_in_Unicode[1];
    UCS2LittleEndian_string[1] = Dash_in_Unicode[0];
    UCS2LittleEndian_string[2] = 0x00;
    UCS2LittleEndian_string[3] = 0x00;

    UCS2LittleEndian_string_length = 4;
  }

  if (Command == SM_FFX_PASTE_QUOTES_1)
  {
    Common_string[0] = '"';
    Common_string[1] = '"';
    Common_string[2] = 0x00;

    UCS2LittleEndian_string[0] = Primary_quote_1_in_Unicode[1];
    UCS2LittleEndian_string[1] = Primary_quote_1_in_Unicode[0];
    UCS2LittleEndian_string[2] = Primary_quote_2_in_Unicode[1];
    UCS2LittleEndian_string[3] = Primary_quote_2_in_Unicode[0];
    UCS2LittleEndian_string[4] = 0x00;
    UCS2LittleEndian_string[5] = 0x00;

    UCS2LittleEndian_string_length = 6;
  }

  if (Command == SM_FFX_PASTE_QUOTES_2)
  {
    Common_string[0] = '"';
    Common_string[1] = '"';
    Common_string[2] = 0x00;

    UCS2LittleEndian_string[0] = Secondary_quote_1_in_Unicode[1];
    UCS2LittleEndian_string[1] = Secondary_quote_1_in_Unicode[0];
    UCS2LittleEndian_string[2] = Secondary_quote_2_in_Unicode[1];
    UCS2LittleEndian_string[3] = Secondary_quote_2_in_Unicode[0];
    UCS2LittleEndian_string[4] = 0x00;
    UCS2LittleEndian_string[5] = 0x00;

    UCS2LittleEndian_string_length = 6;
  }

  PutStringIntoClipboard (Enhancer.Application,
                          Common_string,
                          UCS2LittleEndian_string,
                          UCS2LittleEndian_string_length,
                          Mozilla_internal_format);

  // ���뫠�� � ��।� ���� ᮮ�饭�� WM_MARK. �� ��� ����祭�� �����
  // �㤥� �������� ���ﭨ� ���������� � ���ࠢ��� � ���� ᮮ�饭�� WM_CHAR.
  HMQ Message_queue = WinQueryWindowULong (Input_window, QWL_HMQ);
  WinPostQueueMsg (Message_queue, WM_MARK, (MPARAM) MRK_POST_CTRL_V, (MPARAM) Input_window);

  // ������.
  return;
}

// ��� ����⠭�������� ᮤ�ন��� Clipboard ���

VOID Clipper_RestoreClipboard (VOID)
{
  // ��७�ᨬ � Clipboard �।��騥 �����.
  CHAR Mozilla_internal_format[] = "text/unicode";

  PutStringIntoClipboard (Enhancer.Application,
                          Clipper.RTSettings.Clipboard_data_Text,
                          Clipper.RTSettings.Clipboard_data_UCS2,
                          Clipper.RTSettings.Clipboard_data_UCS2_length,
                          Mozilla_internal_format);

  // �᢮������� ������.
  if (Clipper.RTSettings.Clipboard_data_Text != NULL) { DosFreeMem (Clipper.RTSettings.Clipboard_data_Text); Clipper.RTSettings.Clipboard_data_Text = NULL; }
  if (Clipper.RTSettings.Clipboard_data_UCS2 != NULL) { DosFreeMem (Clipper.RTSettings.Clipboard_data_UCS2); Clipper.RTSettings.Clipboard_data_UCS2 = NULL; }

  Clipper.RTSettings.Clipboard_data_Text_length = 0;
  Clipper.RTSettings.Clipboard_data_UCS2_length = 0;

  // ������.
  return;
}

// ��� ��ࠡ��稪 ᮮ�饭��, ����� �뫨 ��।��� � ��⮪ ���

// Message ��।���� ��襤襥 ᮮ�饭��.
VOID Clipper_ClipperMessageProcessing (PQMSG Message)
{
  // ��⠭�������� �ਮ��� ��⮪�.
  if (Message->msg == SM_PRIORITY)
  {
    // ��⠭�������� �ਮ���.
    LONG Class = (LONG) Message->mp1;
    LONG Delta = (LONG) Message->mp2;
    DosSetPriority (PRTYS_THREAD, Class, Delta, 0);

    // ���������� �ਮ���.
    Enhancer.Modules.Clipper->Priority = MAKELONG (Class, Delta);
  }

  // ����砥� �뤥����� � ⥪�⮢�� ����.
  if (Message->msg == SM_BEGIN_VIO_MARKING || Message->msg == SM_END_VIO_MARKING)
  {
    // ������ ���� ࠬ��.
    HWND Frame_window = (HWND) Message->mp1;

    // �᫨ ���� ��� - ������.
    if (!WinIsWindow (WinQueryAnchorBlock (Frame_window), Frame_window)) return;

    // ����砥� � �몫�砥� �뤥�����.
    if (Message->msg == SM_BEGIN_VIO_MARKING) Clipper_BeginVIOMarking (Frame_window);
    if (Message->msg == SM_END_VIO_MARKING) Clipper_EndVIOMarkingAndCopyText (Frame_window);
  }

  // ���������� �뤥����� ⥪��.
  if (Message->msg == SM_COPY_VIO_TEXT)
  {
    // �᫨ � ⥪�⮢�� ����� �� ���� ���������� ⥪�� - ������.
    if (!Clipper.Settings.Mouse_in_VIO) return;

    // ������ ���� ࠬ��.
    HWND Frame_window = (HWND) Message->mp1;

    // �᫨ ���� ��� - ������.
    if (!WinIsWindow (WinQueryAnchorBlock (Frame_window), Frame_window)) return;

    // �᫨ �뤥����� ⥪�� �� �� ���� - ��稭��� ���.
    if (!Clipper_VIOMarkingIsInProcess (Frame_window)) Clipper_BeginVIOMarking (Frame_window);
    // ���� - �����蠥� �뤥����� � ���������� ⥪��.
    else Clipper_EndVIOMarkingAndCopyText (Frame_window);
  }

  // ��⠢�塞 ⥪�� � ����.
  if (Message->msg == SM_PASTE_VIO_TEXT)
  {
    // �᫨ � ⥪�⮢�� ����� �� ���� ���������� ⥪�� - ������.
    if (!Clipper.Settings.Mouse_in_VIO) return;

    // ������ ���� ࠬ��.
    HWND Frame_window = (HWND) Message->mp1;

    // �᫨ ���� ��� - ������.
    if (!WinIsWindow (WinQueryAnchorBlock (Frame_window), Frame_window)) return;

    // �᫨ � ���� �� ���� �뤥����� ⥪�� - ��⠢�塞 ⥪��.
    if (!Clipper_VIOMarkingIsInProcess (Frame_window)) Clipper_PasteTextToVIOWindow (Frame_window);
  }

  // ���������� ⥪�� �� ����⨨ �।��� ������ ���.
  if (Message->msg == SM_MB_CLICK)
  {
    // ������ ����, � ����� ࠡ�⠥� ���짮��⥫�.
    HWND Input_window = (HWND) Message->mp1;

    // �᫨ ���� ��� - ������.
    if (!WinIsWindow (WinQueryAnchorBlock (Input_window), Input_window)) return;

    // ������ ���� ࠡ�祣� �⮫�.
    HWND Desktop = QueryDesktopWindow ();

    // ������ �६�, �����筮� ��� �������� ������ �� ������ ���.
    LONG DblClk_delta = WinQuerySysValue (Desktop, SV_DBLCLKTIME);

    // �믮��塞 ����প�, �⮡� �������� �������� ������.
    while (1)
    {
      // �᫨ �६� ��᫥����� ������ �� �।��� ������ ��� �������⭮ - �ந��諮 ������� ����⨥, ������.
      // � �� �६� � ��।� ��⮪� 㦥 ����� ᫥���饥 ᮮ�饭�� - SM_MB_DOUBLECLICK.
      if (WMMBDownTime () == 0)
      {
        // �᢮������� 㪠��⥫� ���.
        ResetPointer ();

        // ������.
        return;
      }

      // ������ ⥪�饥 �६�.
      LONG Current_time = WinGetCurrentTime (Enhancer.Application);

      // �᫨ ��諮 �����筮 ����� �६��� - �� � ���浪�.
      if (Current_time > WMMBDownTime ())
       if (Current_time - WMMBDownTime () > DblClk_delta)
        break;

      // �᫨ �६� ��諮 �१ ���� - ������.
      if (Current_time < WMMBDownTime ())
      {
        // �᢮������� 㪠��⥫� ���.
        ResetPointer ();

        // ������.
        return;
      }

      // ��१ �����஥ �६� - ��⠭�������� 㪠��⥫� ��� "�஧�筠� ��५��".
      if (Current_time - WMMBDownTime () > (DblClk_delta / 2))
       if (Resources.Pointer_for_CopyPaste != NULLHANDLE)
        WinSetPointer (QueryDesktopWindow (), Resources.Pointer_for_CopyPaste);

      // �믮��塞 ����প�.
      Retard ();
    }

    // �᢮������� 㪠��⥫� ���.
    ResetPointer ();

    // �६� ��᫥����� ������ �� �।��� ������ ��� - �������⭮.
    DiscardWMMBDownTime ();

    // ������ �᪮�⥫� ��� �⮣� ����.
    LONG Accelerator = (LONG) Message->mp2;

    // ���������� ⥪�� � ����.
    ClipboardMouseAction (Input_window, MOUSE_CLIPBOARD_COPY, Accelerator);
  }

  // ��⠢�塞 ⥪�� � ���� �� ����⨨ �।��� ������ ���.
  if (Message->msg == SM_MB_DOUBLECLICK)
  {
    // ������ ����, � ����� ࠡ�⠥� ���짮��⥫�.
    HWND Input_window = (HWND) Message->mp1;

    // �᫨ ���� ��� - ������.
    if (!WinIsWindow (WinQueryAnchorBlock (Input_window), Input_window)) return;

    // �᫨ ������ ��� ᭮�� �뫠 ����� - ������.
    if (WMMBDownTime ()) return;

    // ������ �᪮�⥫� ��� �⮣� ����.
    LONG Accelerator = (LONG) Message->mp2;

    // ��⠢�塞 ⥪�� � ����.
    ClipboardMouseAction (Input_window, MOUSE_CLIPBOARD_PASTE, Accelerator);
  }

  // ��⠢�塞 ⥪�� � ���� Mozilla �� ����⨨ FireFox-������.
  if (Message->msg >= SM_FFX_PASTE_FIRST && Message->msg <= SM_FFX_PASTE_LAST)
  {
    // ������ ����, � ����� ࠡ�⠥� ���짮��⥫�.
    HWND Input_window = (HWND) Message->mp1;

    // �᫨ ���� ��� - ������.
    if (!WinIsWindow (WinQueryAnchorBlock (Input_window), Input_window)) return;

    // ��⠢�塞 ⥪�� � ����.
    Clipper_PasteFireFoxCharacters (Input_window, Message->msg);
  }

  // ����⠭�������� ᮤ�ন��� Clipboard.
  if (Message->msg == SM_RESTORE_CLIPBOARD) Clipper_RestoreClipboard ();

  // ������.
  return;
}

// ��� ��⮪ ��� �뤥����� ��ப � ����� ���

VOID Clipper_ClipperThread (VOID)
{
  // ��।��塞 ��⮪ � ��⥬�.
  HAB Thread = WinInitialize (0);

  // �᫨ �� ᤥ���� �� 㤠���� - ��室.
  if (Thread == NULLHANDLE)
  {
    // �� ᮧ����� ��⮪� �ந��諠 �訡��.
    Thread_responds.Thread_is_created = -1;

    // ��室.
    return;
  }

  // ������� ��।� ᮮ�饭�� - ��� ������ ���� � ������ ��⮪�.
  HMQ Message_queue = WinCreateMsgQueue (Thread, 0); Enhancer.Modules.Clipper->Message_queue = Message_queue;

  // �᫨ ��।� ᮧ���� �� 㤠���� - ��室.
  if (Enhancer.Modules.Clipper->Message_queue == NULLHANDLE)
  {
    // �����蠥� ࠡ��� ��⮪�.
    WinTerminate (Thread);

    // �� ᮧ����� ��⮪� �ந��諠 �訡��.
    Thread_responds.Thread_is_created = -1;

    // ��室.
    return;
  }

  // ��⮪ ᮧ��� �ᯥ譮.
  Thread_responds.Thread_is_created = 1;

  // ����祭�� � ��ࠡ�⪠ ᮮ�饭��, ��室��� � ��⮪.
  QMSG Message = {0};
  while (WinGetMsg (Thread, &Message, 0, 0, 0))
  {
    // �஢��塞, �� ���� �� ᫥��� ⠪�� �� ᮮ�饭��.
    QMSG Next_message = {0};
    WinPeekMsg (Thread, &Next_message, NULLHANDLE, Message.msg, Message.msg, PM_NOREMOVE);
    if (Next_message.msg == Message.msg)
     if (Next_message.mp1 == Message.mp1)
      if (Next_message.mp2 == Message.mp2)
       if (Next_message.hwnd == Message.hwnd) continue;

    // ��ࠡ��뢠�� ᮮ�饭��.
    Clipper_ClipperMessageProcessing (&Message);
  }

  // �����蠥� ࠡ��� ��⮪�.
  WinDestroyMsgQueue (Message_queue);
  WinTerminate (Thread);
  DosExit (EXIT_THREAD, 0);
}
