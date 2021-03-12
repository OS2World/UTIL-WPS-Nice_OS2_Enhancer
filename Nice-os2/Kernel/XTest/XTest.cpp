#define DEBUG_VERSION
#include "Nice-os2.cpp"

// ��� �ਫ������ ���

VOID XTest (HAB Application)
{
  /*

  // ������ ����� ��������� � ���⨭��.
  INT TitleBar_height = WinQuerySysValue (QueryDesktopWindow (), SV_CYMINMAXBUTTON);

  Log ("TitleBar height:"); Log (TitleBar_height);

  */


  /*

  // ����, ���� �㤥� ����祭 "Scroll Lock".
  while (1)
  {
    BYTE Keyboard_state[256]; bzero (Keyboard_state, sizeof (BYTE) * 256);
    WinSetKeyboardStateTable (QueryDesktopWindow (), Keyboard_state, 0);

    if (Keyboard_state[VK_SCRLLOCK]) break;
    else DosSleep (1);
  }

  // ������ ����, ��� ����� �ᯮ����� 㪠��⥫� ���.
  POINT Pointer = {0}; WinQueryPointerPos (QueryDesktopWindow (), &Pointer);
  HWND Window = WinWindowFromPoint (QueryDesktopWindow (), &Pointer, 1);
  HWND Frame_window = QueryFrameWindow (Window);

  // �᫨ �� ���� VirtualPC � ��� ��࠭�:
  if (IsOdinFrameWindow (Frame_window) && WindowIsActive (Frame_window))
  {
    // ���뫠�� ᮮ�饭�� � ����.
    while (1)
    {
      // ������ �ᯮ������� ���� ࠬ��.
      SWP Wp = {0}; WinQueryWindowPos (Frame_window, &Wp);

      // ���뫠�� ���� ᮮ�饭�� �� ���������� � ���.
      WinSetPointerPos (QueryDesktopWindow (), Wp.x + 1010, Wp.y + 35);
      WinPostMsg (Window, WM_BUTTON1DOWN, MRFROM2SHORT (0, 0), MRFROM2SHORT (HT_NORMAL, KC_NONE));
      WinPostMsg (Window, WM_BUTTON1UP, MRFROM2SHORT (0, 0), MRFROM2SHORT (HT_NORMAL, KC_NONE));

      DosSleep (250);

      WinSetPointerPos (QueryDesktopWindow (), Wp.x + 285, Wp.y + 75);
      WinPostMsg (Window, WM_BUTTON1DOWN, MRFROM2SHORT (0, 0), MRFROM2SHORT (HT_NORMAL, KC_NONE));
      WinPostMsg (Window, WM_BUTTON1UP, MRFROM2SHORT (0, 0), MRFROM2SHORT (HT_NORMAL, KC_NONE));

      DosSleep (100);

      MPARAM First_parameter_1 = 0; MPARAM Second_parameter_1 = 0;
      MPARAM First_parameter_2 = 0; MPARAM Second_parameter_2 = 0;
      ComposeWMCharMessage (&First_parameter_1, &Second_parameter_1, &First_parameter_2, &Second_parameter_2, SC_DELETE, 0, 0);
      WinPostMsg (Window, WM_CHAR, First_parameter_1, Second_parameter_1);
      WinPostMsg (Window, WM_CHAR, First_parameter_2, Second_parameter_2);

      DosSleep (1000);

      // �஢��塞, ����祭 �� �� "Scroll Lock".
      BYTE Keyboard_state[256]; bzero (Keyboard_state, sizeof (BYTE) * 256);
      WinSetKeyboardStateTable (QueryDesktopWindow (), Keyboard_state, 0);

      if (!Keyboard_state[VK_SCRLLOCK]) break;
    }
  }

  */


  /*

  // ������ ᮤ�ন��� Clipboard.
  BYTE Common_string[1024] = "";
  LONG Common_string_length = 1024;
  BYTE UCS2LittleEndian_format[] = "text/unicode";
  BYTE UCS2LittleEndian_string[2048] = "";
  LONG UCS2LittleEndian_string_length = 2048;

  GetStringFromClipboard (Application,
                          Common_string,
                          Common_string_length,
                          UCS2LittleEndian_string,
                          UCS2LittleEndian_string_length,
                          UCS2LittleEndian_format);

  Log (Common_string);

  Log (UCS2LittleEndian_string[0]);
  Log (UCS2LittleEndian_string[1]);
  Log (UCS2LittleEndian_string[2]);
  Log (UCS2LittleEndian_string[3]);
  Log (UCS2LittleEndian_string[4]);
  Log (UCS2LittleEndian_string[5]);
  Log (UCS2LittleEndian_string[6]);
  Log (UCS2LittleEndian_string[7]);
  Log (UCS2LittleEndian_string[8]);

  */


  /*

  // ��ॡ�ࠥ� ���� � ���� ࠡ�祣� �⮫�.
  HENUM Enumeration = WinBeginEnumWindows (QueryDesktopWindow ()); HWND Window = NULLHANDLE;
  while ((Window = WinGetNextWindow (Enumeration)) != NULLHANDLE)
  {
    // ...
  }
  WinEndEnumWindows (Enumeration);

  */

  // ������.
  return;
}

INT Main (INT argc, CHAR *argv[])
{
  // ��।��塞 �ਫ������ � ��⥬�.
  HAB Application = WinInitialize (0);

  // �᫨ �� ᤥ���� �� 㤠���� - ��室.
  if (Application == NULLHANDLE)
  {
    // ��� - �訡��.
    WinAlarm (HWND_DESKTOP, WA_ERROR);
    // ��室.
    return 0;
  }

  // ������� ��।� ᮮ�饭��.
  HMQ Message_queue = WinCreateMsgQueue (Application, 0);

  // �᫨ ��।� ᮧ���� �� 㤠���� - ��室.
  if (Message_queue == NULLHANDLE)
  {
    // ��� - �訡��.
    WinAlarm (HWND_DESKTOP, WA_ERROR);
    // ��室.
    WinTerminate (Application); return 0;
  }

  WinMessageBox (HWND_DESKTOP, NULLHANDLE, "Ready...", "", 0, 0);

  /*

  InitKernel (Application, 0, NULLHANDLE);
  SetPreDefinedSettings (SET_ALL_SETTINGS);

  */

  // �믮��塞 ����⢨�.
  DosForceDelete ("_log.txt");
  Enhancer.Application = Application; XTest (Application);

  // ����뢠�� ��।� ᮮ�饭��.
  WinDestroyMsgQueue (Message_queue);

  // ��室.
  WinTerminate (Application); return 0;
}
