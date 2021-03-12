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

// ─── Обработчик сообщений для окна ───

// Поток приложения вызывает WindowProc всякий раз, когда для окна есть сообщение.
// Window - окно, Message - сообщение, *_parameter - данные, которые передаются вместе с сообщением.
MRESULT EXPENTRY DialogWindow_DlgProc (HWND Window, ULONG Message, MPARAM First_parameter, MPARAM Second_parameter)
{
  // Проверяем сообщение.
  switch (Message)
  {
    // Выполняем действия при создании окна.
    // Эти сообщения не передаются обработчику диалога.
    // Сообщение "WM_INITDLG" приходит в то время, когда окно еще не показано, а
    // сообщение "MY_INITDLG" приходит окну уже после начала обработки сообщений.
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

    // Отображаем настройки.
    // Это сообщение не передается обработчику диалога.
    case MY_SHOW_SETTINGS:
    {
      DialogWindow_ShowSettings (Window, Message, First_parameter, Second_parameter);
    }
    return 0;

    // Следим за полями ввода.
    // Это сообщение не передается обработчику диалога.
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

    // Обрабатываем нажатия на кнопки.
    // Это сообщение не передается обработчику диалога.
    case WM_COMMAND:
    {
      ULONG WM_Control_Button_ID = SHORT1FROMMP (First_parameter);

      // Запускаем/останавливаем поток.
      if (WM_Control_Button_ID == ID_MAINWNDFORM_START_BUTTON)
      {
        DialogWindow_GoButton (Window, Message, First_parameter, Second_parameter);
      }

      // Показываем справочник.
      if (WM_Control_Button_ID == ID_MAINWNDFORM_HELP_BUTTON)
      {
        DialogWindow_HelpButton (Window, Message, First_parameter, Second_parameter);
      }

      // Закрываем окно.
      if (WM_Control_Button_ID == ID_MAINWNDFORM_STOP_BUTTON)
      {
        DialogWindow_StopButton (Window, Message, First_parameter, Second_parameter);
      }
    }
    return 0;

    // Обрабатываем нажатия на клавиши.
    // Это сообщение не передается обработчику диалога.
    case WM_CHAR:
    {
      // Смотрим, какая клавиша нажата.
      BYTE Scan_code = CHAR4FROMMP (First_parameter);

      // Если это клавиша F1:
      if (Scan_code == SC_F1)
      {
        // Показываем справочник.
        WinPostMsg (Window, WM_COMMAND, (MPARAM) ID_MAINWNDFORM_HELP_BUTTON, 0);
      }

      // Если это клавиша Esc:
      if (Scan_code == SC_ESC)
      {
        // Ничего не делаем.
        return 0;
      }
    }
    return 0;

    // Выполняем действия при закрытии окна.
    // Это сообщение появляется после "WM_SYSCOMMAND:SC_CLOSE" от обработчика "WC_FRAME",
    // и не передается обработчику диалога (нулевое значение = разрешение закрытия окна).
    case WM_CLOSE:
    {
      DialogWindow_Close (Window, Message, First_parameter, Second_parameter);

      // Завершаем диалог.
      WinDismissDlg (Window, 0);
    }
    return 0;
  }

  // Возврат.
  return WinDefDlgProc (Window, Message, First_parameter, Second_parameter);
}
