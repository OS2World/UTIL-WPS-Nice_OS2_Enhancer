#include "Pages\\DialogWindow\\Routines\\Dialog_Init.cpp"
#include "Pages\\DialogWindow\\Routines\\Dialog_Close.cpp"

#include "Pages\\DialogWindow\\Routines\\Settings_Show.cpp"

#include "Pages\\DialogWindow\\Routines\\CheckBox_Names.cpp"
#include "Pages\\DialogWindow\\Routines\\CheckBox_LongNames.cpp"
#include "Pages\\DialogWindow\\Routines\\CheckBox_Icons.cpp"
#include "Pages\\DialogWindow\\Routines\\CheckBox_Type.cpp"
#include "Pages\\DialogWindow\\Routines\\CheckBox_ReadOnly.cpp"

#include "Pages\\DialogWindow\\Routines\\Field_Path.cpp"

#include "Pages\\DialogWindow\\Routines\\Button_Go.cpp"
#include "Pages\\DialogWindow\\Routines\\Button_Help.cpp"
#include "Pages\\DialogWindow\\Routines\\Button_Stop.cpp"

// ��� ��ࠡ��稪 ᮮ�饭�� ��� ���� ���

// ��⮪ �ਫ������ ��뢠�� WindowProc ��直� ࠧ, ����� ��� ���� ���� ᮮ�饭��.
// Window - ����, Message - ᮮ�饭��, *_parameter - �����, ����� ��।����� ����� � ᮮ�饭���.
MRESULT EXPENTRY DialogWindow_DlgProc (HWND Window, ULONG Message, MPARAM First_parameter, MPARAM Second_parameter)
{
  // �஢��塞 ᮮ�饭��.
  switch (Message)
  {
    // �믮��塞 ����⢨� �� ᮧ����� ����.
    // �� ᮮ�饭�� �� ��।����� ��ࠡ��稪� �������.
    // ����饭�� "WM_INITDLG" ��室�� � � �६�, ����� ���� �� �� ��������, �
    // ᮮ�饭�� "MY_INITDLG" ��室�� ���� 㦥 ��᫥ ��砫� ��ࠡ�⪨ ᮮ�饭��.
    case WM_INITDLG:
    {
      WinPostMsg (Window, MY_INITDLG, 0, 0);
    }
    return DLG_NOFOCUS;

    case MY_INITDLG:
    {
      DialogWindow_Init (Window, Message, First_parameter, Second_parameter);
      WinPostMsg (Window, MY_SHOW_SETTINGS, 0, 0);
    }
    return 0;

    // �⮡ࠦ��� ����ன��.
    // �� ᮮ�饭�� �� ��।����� ��ࠡ��稪� �������.
    case MY_SHOW_SETTINGS:
    {
      DialogWindow_ShowSettings (Window, Message, First_parameter, Second_parameter);
    }
    return 0;

    // ������ �� ���ﬨ �����.
    // �� ᮮ�饭�� �� ��।����� ��ࠡ��稪� �������.
    case WM_CONTROL:
    {
      ULONG WM_Control_Window_ID = SHORT1FROMMP (First_parameter);
      ULONG WM_Control_Action_ID = SHORT2FROMMP (First_parameter);

      if (WM_Control_Window_ID == ID_MAINWNDFORM_NAMES_CHECKBOX)
      {
        switch (WM_Control_Action_ID)
        {
          case BN_CLICKED:
          case BN_DBLCLICKED:
          {
            DialogWindow_NamesCheckBox (Window, Message, First_parameter, Second_parameter, WM_Control_Window_ID);
            WinPostMsg (Window, MY_SHOW_SETTINGS, 0, 0);
          }
          break;
        }
      }

      if (WM_Control_Window_ID == ID_MAINWNDFORM_LONGNAMES_CHECKBOX)
      {
        switch (WM_Control_Action_ID)
        {
          case BN_CLICKED:
          case BN_DBLCLICKED:
          {
            DialogWindow_LongNamesCheckBox (Window, Message, First_parameter, Second_parameter, WM_Control_Window_ID);
            WinPostMsg (Window, MY_SHOW_SETTINGS, 0, 0);
          }
          break;
        }
      }

      if (WM_Control_Window_ID == ID_MAINWNDFORM_ICONS_CHECKBOX)
      {
        switch (WM_Control_Action_ID)
        {
          case BN_CLICKED:
          case BN_DBLCLICKED:
          {
            DialogWindow_IconsCheckBox (Window, Message, First_parameter, Second_parameter, WM_Control_Window_ID);
            WinPostMsg (Window, MY_SHOW_SETTINGS, 0, 0);
          }
          break;
        }
      }

      if (WM_Control_Window_ID == ID_MAINWNDFORM_TYPE_CHECKBOX)
      {
        switch (WM_Control_Action_ID)
        {
          case BN_CLICKED:
          case BN_DBLCLICKED:
          {
            DialogWindow_TypeCheckBox (Window, Message, First_parameter, Second_parameter, WM_Control_Window_ID);
            WinPostMsg (Window, MY_SHOW_SETTINGS, 0, 0);
          }
          break;
        }
      }

      if (WM_Control_Window_ID == ID_MAINWNDFORM_READONLY_CHECKBOX)
      {
        switch (WM_Control_Action_ID)
        {
          case BN_CLICKED:
          case BN_DBLCLICKED:
          {
            DialogWindow_ReadOnlyCheckBox (Window, Message, First_parameter, Second_parameter, WM_Control_Window_ID);
            WinPostMsg (Window, MY_SHOW_SETTINGS, 0, 0);
          }
          break;
        }
      }

      if (WM_Control_Window_ID == ID_MAINWNDFORM_PATH_FIELD)
      {
        switch (WM_Control_Action_ID)
        {
          case EN_CHANGE:
          {
            DialogWindow_PathField (Window, Message, First_parameter, Second_parameter, WM_Control_Window_ID);
          }
          break;
        }
      }
    }
    return 0;

    // ��ࠡ��뢠�� ������ �� ������.
    // �� ᮮ�饭�� �� ��।����� ��ࠡ��稪� �������.
    case WM_COMMAND:
    {
      ULONG WM_Control_Button_ID = SHORT1FROMMP (First_parameter);

      // ����᪠��/��⠭�������� ��⮪.
      if (WM_Control_Button_ID == ID_MAINWNDFORM_START_BUTTON)
      {
        DialogWindow_GoButton (Window, Message, First_parameter, Second_parameter);
      }

      // �����뢠�� �ࠢ�筨�.
      if (WM_Control_Button_ID == ID_MAINWNDFORM_HELP_BUTTON)
      {
        DialogWindow_HelpButton (Window, Message, First_parameter, Second_parameter);
      }

      // ����뢠�� ����.
      if (WM_Control_Button_ID == ID_MAINWNDFORM_STOP_BUTTON)
      {
        DialogWindow_StopButton (Window, Message, First_parameter, Second_parameter);
      }
    }
    return 0;

    // ��ࠡ��뢠�� ������ �� ������.
    // �� ᮮ�饭�� �� ��।����� ��ࠡ��稪� �������.
    case WM_CHAR:
    {
      // ����ਬ, ����� ������ �����.
      BYTE Scan_code = CHAR4FROMMP (First_parameter);

      // �᫨ �� ������ F1:
      if (Scan_code == SC_F1)
      {
        // �����뢠�� �ࠢ�筨�.
        WinPostMsg (Window, WM_COMMAND, (MPARAM) ID_MAINWNDFORM_HELP_BUTTON, 0);
      }

      // �᫨ �� ������ Esc:
      if (Scan_code == SC_ESC)
      {
        // ��祣� �� ������.
        return 0;
      }
    }
    return 0;

    // �믮��塞 ����⢨� �� �����⨨ ����.
    // �� ᮮ�饭�� ������ ��᫥ "WM_SYSCOMMAND:SC_CLOSE" �� ��ࠡ��稪� "WC_FRAME",
    // � �� ��।����� ��ࠡ��稪� ������� (�㫥��� ���祭�� = ࠧ�襭�� ������� ����).
    case WM_CLOSE:
    {
      DialogWindow_Close (Window, Message, First_parameter, Second_parameter);

      // �����蠥� ������.
      WinDismissDlg (Window, 0);
    }
    return 0;
  }

  // ������.
  return WinDefDlgProc (Window, Message, First_parameter, Second_parameter);
}
